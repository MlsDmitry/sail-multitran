import QtQuick 2.2
import Sailfish.Silica 1.0
import harbour.multitran 1.0
import "../dialogs" as Dialogs
import "../components" as Components

Page {

    Dialogs.LangChoose {
        id: langChooseDialog
    }

    //    SilicaFlickable {
    //        width: parent.width
    //        height: parent.height
    ////        contentHeight: header.height + searchField.height

    //        VerticalScrollDecorator {}

    //        PageHeader {
    //            id: header

    //            title: "Multitran"
    //        }

    //        PullDownMenu {
    //            MenuItem {
    //                text: "Choose translation language"
    ////                onClicked: pageStack.push(langChooseDialog)
    //                onClicked: console.log("Menu item clicked")
    //            }
    //        }

    //        TextField {
    //            id: searchField

    //            anchors.top: header.bottom

    //            placeholderText: "Enter term to translate"

//                onTextChanged: {
//                    core.onSearchTextChanged(text)
//                    console.log(text)
//                }

//                onFocusChanged: suggestionView.visible = focus;
//            }

//            Connections {
//                target: core

//                onCompletionTermsReceived: {
//                    console.log("onCompletionTermsReceived from js");
//                }
//            }

    //    }

    SilicaFlickable {
        anchors.fill: parent

        VerticalScrollDecorator {}

        PageHeader {
            id: header

            title: "Multitran"
        }

        PullDownMenu {
            MenuItem {
                text: "Choose translation language"
                onClicked: pageStack.push(langChooseDialog)
                //                onClicked: console.log("Menu item clicked")
            }
        }

        TextField {
            anchors.top: header.bottom

            id: searchField

            placeholderText: "Enter term to translate"

            onTextChanged: {
                suggestionListModel.getSuggestions(text, core.toLang, core.fromLang)
                console.log(text)
            }

            onFocusChanged: {
                translationView.visible = !focus;
                suggestionView.visible = focus;
            }
        }

//        Connections {
//            target: core

//            onCompletionTermsReceived: {
//                console.log("onCompletionTermsReceived from js");
//            }
//        }


        SuggestionListModel {
            id: suggestionListModel

            transport: core.transport
        }

        TranslationListModel {
            id: translationListModel

            transport: core.transport
        }

        SilicaListView {
            id: suggestionView

            anchors {
                top: searchField.bottom
                bottom: parent.bottom
            }
            width: parent.width
            height: parent.height

            visible: false

            model: suggestionListModel

            delegate: ListItem {
                Label {
                    text: display
                }
                onClicked: {
                    translationView.visible = true;
                    searchField.text = display
                    translationListModel.getTranslations(display, core.toLang, core.fromLang);
                }
            }

            VerticalScrollDecorator {}
        }

        SilicaListView {
            id: translationView

            anchors {
                top: searchField.bottom
                bottom: parent.bottom
            }

            width: parent.width
            height: parent.height

            section {
                property: "spart"
                criteria: ViewSection.FullString
                delegate: SectionHeader {
                    text: section
//                    color: Theme.highlightColor
                }
            }

            delegate: Label {
                    text: translation
                }

            model: translationListModel

            VerticalScrollDecorator {}
        }

    }

    //    Components.SuggestionListView {
    //        id: suggestionView

    //        anchors.fill: parent
    //        anchors.top: searchField.bottom

    //    }


}
