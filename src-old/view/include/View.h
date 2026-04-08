#ifndef VIEW_H
#define VIEW_H

#include <string>

/**
 * General interface for all view components in a game of Battleship.
 * At its most basic, all components may display the game, or display an error.
 */
class View {
    public:

    /**
     * Renders the component's game state according to the implementation.
     * This may be used as a refresh in a GUI, or an occasional update in a TUI.
     */
    virtual void render() = 0;

    /**
     * Displays an error message to the user.
     *
     * @param message the message to show
     */
    virtual void denyAction(std::string message) = 0;

    virtual ~View() = default;
};

#endif