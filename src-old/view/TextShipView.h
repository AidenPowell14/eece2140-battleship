#ifndef TEXT_SHIP_VIEW_H
#define TEXT_SHIP_VIEW_H

#include "include/ShipView.h"
#include "include/BuildListener.h"
#include "../model/include/Ship.h"
#include <string>

#define WATER "W"
#define SHIP "S"
#define STRIKE "X"

/**
 * Concrete instance of a ShipView meant for text-based user interfaces.
 * The grid is labeled with numbers for columns and numbers for rows.
 * The textual representation of the water, ships, and hits, can be verified
 * with the preprocessor definitions above.
 */
class TextShipView : public ShipView {
    private:
    // supplement necessary fields and constructor. 
    // implement custom destructor if you allocate special resources.

    BuildListener* controller;

    public:

    TextShipView() {}

    // View
    void render() override;

    // View
    void denyAction(std::string message) override;

    // ShipView
    void promptPlace(const Ship& ship) override {
        ship.size();
    }

    // ShipView
    void setListener(BuildListener* controller) override;
};

#endif