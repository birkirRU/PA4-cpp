# PA4 - Inscryption style card game

## User section

**Run:** `make` then `./game`

The game of this game is Inscryption, is a well known board. The rules are simple. You have a board with 3 rows. First row, is the preRow for the enemy. The second row, is the current enemies active cards and the last row is our current active cards. This game is turn based, but we can see what the enemy will play next round, with the preRow. All the cards from the preRow move straight down, so card at index 1 moves to the same index but at lower row. 

All the cards attack the next cards ahead of them. We have 6 types of cards: Raven, Bullfrog, GreatWhite, Squirrel, Wolfcup and Wolf. All have special abilites called sigils. For sigils we have: WATERBORNE, MIGHTY_LEAP, FLEDGING and AIRBORNE. Cards attack what is infront of them, if there is a card it attacks it and deducted HP from it. If there isnt a card in front of it, the player missess HP and is added to us. If the player doesn't have any HP left, we win. If we don't have HP, we lose. 

In the turn, you can either choose a card from the deck or a squirrel, which will be added to your hand. Cards have blood costs, which means you have to sacrifice another cards for it, to be able to place it. Squirrel is often used to build of blood cost. On each card we can see "C", which stands for blood cost. Also we can see "Number/AnotherNumber". The first number stands for HP, and the second the damage. The last one is a shortcut for the sigils. 

MIGHTY_LEAP: It blocks airborne sigils.

FLEDGING: Upgrades your character after the first round, So WolfCup becomes Wolf. 

AIRBORNE: For 1 turn, your player can attack through the card and straight to the player.

WATERBORNE: For 1 turn, your card cant be attacked, and instead the damage is taken out of the player. 

**Commands:** 

When placing a card first input and number of the card followed with space and then the index, if you don't want to move more type "done". For example: "1 2"

You will also be asked if you want to draw a card or a squirrel. Please answer with "c" or "s".



## 2. Programmer section

**Structure:** 

**Polymorphism:** 

**Extend:** 
