import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: langChooseDialog
    anchors {
//        fill: parent
        leftMargin: Theme.horizontalPageMargin
        rightMargin: Theme.horizontalPageMargin
    }

    property alias searchField: fromLang

    Column {
        id: headerContainer

        width: parent.width

        DialogHeader {
            id: header
            dialog: langChooseDialog

            title: "Language choose"
        }

        Row {
            id: searchFieldContainer

            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            width: parent.width
            spacing: 5

            TextField {
                id: fromLang

                width: parent.width / 2

                placeholderText: "From lang"

                onFocusChanged: {
                    if (focus)
                        model.reload(this);
                    else
                        model.display();
                }

                onTextChanged: {
                    model.reload(this);
                }

            }

            TextField {
                id: toLang

                width: parent.width / 2

                placeholderText: "To lang"

                onFocusChanged: {
                    if (focus)
                        model.reload(this);
                    else
                        model.display();
                }

                onTextChanged: {
                    model.reload(this);
                }
            }
        }
    }

    SilicaListView {

        id: languageList

        anchors {
            top: headerContainer.bottom
        }

        width: parent.width
        height: parent.height

        property TextField lastTextField: fromLang

        VerticalScrollDecorator {}

        model: ListModel {
            id: model

            property var languages: {
                "Arabic": 10,
                "Bulgarian": 15,
                "Chinese": 17,
                "Croatian": 8,
                "Czech": 16,
                "Danish": 22,
                "Dutch": 24,
                "English": 1,
                "Estonian": 26,
                "Finnish": 36,
                "French": 4,
                "German": 3,
                "Greek": 38,
                "Hungarian": 42,
                "Irish": 49,
                "Italian": 23,
                "Japanese": 28,
                "Korean": 39,
                "Latin": 37,
                "Latvian": 27,
                "Lithuanian": 12,
                "Maltese": 78,
                "Norwegian": 30,
                "Polish": 14,
                "Portuguese": 11,
                "Romanian": 13,
                "Russian": 2,
                "Slovak": 60,
                "Slovenian": 67,
                "Spanish": 5,
                "Swedish": 29,
                "Turkish": 32,
                "Ukrainian": 33,
            }

            Component.onCompleted: display()

            function reload(searchField) {
                model.clear();

                languageList.lastTextField = searchField;

                for (var lang in languages) {
                    if (searchField.text === "" || lang.toLowerCase().indexOf(searchField.text.toLowerCase()) >= 0)
                        append({ "lang": lang });
                }
            }

            function display() {
                for (var lang in languages)
                    append({ "lang": lang })
            }
        }


        delegate: BackgroundItem {
            width: parent.width
            height: Theme.itemSizeMedium
            contentHeight: Theme.itemSizeMedium

            onClicked: {
                languageList.lastTextField.text = label.text;
                languageList.lastTextField.focus = false;

                if (languageList.lastTextField == fromLang)
                    toLang.focus = true;
            }

            Label {
                id: label

                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: Theme.horizontalPageMargin
                }

                font.pixelSize: Theme.fontSizeMedium

                text: lang
            }
        }
    }

}
