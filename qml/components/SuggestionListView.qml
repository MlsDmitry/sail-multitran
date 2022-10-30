import QtQuick 2.2
import Sailfish.Silica 1.0
import harbour.multitran 1.0

SilicaFlickable {

    SuggestionListModel {
        id: suggestionListModel

        transport: core.transport
    }

    SilicaListView {
        anchors.fill: parent

        model: suggestionListModel

        delegate: ListItem {
            Label {
                text: display
            }
        }

        VerticalScrollDecorator {}
    }
}
