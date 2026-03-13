#include "battle_manager.h"


void BattleManager::battle() {
    
    initBattle();
    while (!player.isDead() && !enemy.isDead()) {
        initializeTurn();
        playTurn();
    }

    if (player.isDead()) {
        std::cout << "Enemy wins!" << "\n";
    } else {
        std::cout << "You win!" << "\n";
    }
}

void BattleManager::initBattle() {
    player.shuffleDeck();
    enemy.shuffleDeck();
    player.drawStartingHand();
    enemy.drawStartingHand();
}

void BattleManager::initializeTurn() {

    board.printFullBoard();

    // need to find a way to only force draw single squirrel when its you first turn.
    // Player always starts with single squirrel in hand, and 3 random drawn cards


    // this is wrong, you are only allowed to draw either a regular card or a squirrel.
    std::string temp;
    std::cout << "Do you want to draw a card?: (yes/no) ";
    std::cin >> temp;

    if (temp == "yes") {
        player.drawCard();
    }
    std::cout << "Do you want to draw a squirrel?: (yes/no) ";
    std::cin >> temp;

    if (temp == "yes") {
        player.drawSquirrel();
    }

    std::cout << "Here is your hand: " << "\n";
    board.printHand(player.hand);

    player.playCard(board);
}

void BattleManager::playTurn() {
    // This needs to be changed. 
    // The enemy should place cards to PreEnemy row only at end of players turn
    // all cards in PreEnemy row should be moved to Enemy row at the start of enemy turn . 
    // and then its attack should be resolved 
    //     This could be implamented in the Board class.
    enemy.drawCard();
    if (!enemy.hand.empty()) {
        for (int s = 0; s < 3; ++s) {
            if (!board.enemyActiveCards[s]) {
                Card* c = enemy.hand[0];
                board.placeCard(entityType::ENEMY, c, s);
                enemy.hand.erase(enemy.hand.begin());
                std::cout << "Enemy placed " << c->name << " in slot " << s << "." << "\n";
                break;
            }
        }
    }
    board.resolveCombat(entityType::PLAYER);
    board.resolveCombat(entityType::ENEMY);
    board.onTurnEnd();
}
