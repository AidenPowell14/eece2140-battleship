#include "TextShipView.h"
#include "../model/include/Ship.h"
#include "include/BuildListener.h"
#include <string>


TextShipView::TextShipView() {

}

void TextShipView::render() {

}

void TextShipView::denyAction(std::string message) {

}

void TextShipView::promptPlace(const Ship& ship) {
    
}

void TextShipView::setListener(BuildListener* controller) {
    this->controller = controller;
}