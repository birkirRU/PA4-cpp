# PA4 - Inscryption style card game

## User section

**Run:** `make` then `./game`

The game is inspired by Inscryption, which is a well known board game. The rules are simple. You have a board with 3 rows. First row, is the preRow for the enemy. The second row, is the current enemies active cards and the last row is our current active cards. This game is turn based, but we can see what the enemy will play next round, with the preRow. All the cards from the preRow move straight down, so card at index 1 moves to the same index but at lower row (For the enemy, but our cards don't move). 

All the cards attack the next cards ahead of them. We have 6 types of cards: Raven, Bullfrog, GreatWhite, Squirrel, Wolfcup and Wolf. All have special abilities called sigils. For sigils we have: WATERBORNE, MIGHTY_LEAP, FLEDGING and AIRBORNE. Cards attack what is in front of them, if there is a card it attacks it and deducts HP from it. If there isn't a card in front of it, that damage is dealt to the opposing player. If the player doesn't have any HP left, we win. If we don't have HP, we lose. Remember, if a card doesn't have a card in front of it, it attacks the player. 

In the turn, you can either choose a card from the deck or a squirrel, which will be added to your hand. Cards have blood costs, which means you have to sacrifice another cards for it, to be able to place it. Squirrel is often used to build up blood. On each card we can see "C", which stands for blood cost. Also we can see "Number/AnotherNumber". The first number stands for HP, and the second the damage. The last one is a shortcut for the sigils. If a card has a higher damage than the other cards HP, the card is killed and also the player receives damage. 

In each turn, you can either choose a card from the deck (Which is a random card from the deck) or a squirrel.

Sigils:

    MIGHTY_LEAP: It blocks airborne sigils.

    FLEDGING: Upgrades your character after the first round, So WolfCup becomes Wolf. 

    AIRBORNE: For 1 turn, your player can attack through the card and straight to the player.

    WATERBORNE: The defender doesn't block; damage goes to the opposing player. 

**Commands:** 

When placing a card first input and number of the card and then the index, if you don't want to move any cards type "done". 

You will also be asked if you want to draw a card or a squirrel. Please answer with "c" or "s".

## 2. Programmer section

**Inheritance and Polymorphism**
The game uses inheritance and polymorphism. Player and Enemy both inherit from the Entity type. They therefore share the methods health, hand, deck and drawCard(). The usage of drawCard() differs since Player and Enemy behave differently. Combat rules are handled inside the sigil hierarchy, the board gets a Sigil* from SigilRegister::getSigil() and calls virtual methods such as canBlock() and onTurnEnd(), so each sigil type implements its own logic without the board needing to know the concrete type.

**Templates**
The game also uses templates, the deck adds cards using the template method addCard<CardType>() in Deck, so we can create the correct card type in one place by doing addCard<Wolf> and addCard<Squirrel> for example.

**Structure:**
The main flow of the game goes inside BattleManager. There the game runs turns, calls the board for combat and printing, and uses the player/enemy entities for drawing and playing. The board has 3 lanes/positions and uses CombatContext to pass attackers, blockers and game states into sigil.

**Extend:**
To add a new card to the game, you have to create a class that inherits from Card inside card.h, then use deckObj.addCard<YourNewCard>() in the Player or Enemy constructor depending on where you want to use it. To add a new sigil, add a value to the enum SigilName, implement a class that inherits from Sigil and override or use the right methods, and register it in SigilRegister inside sigil.cpp. The board and combat logic already use Sigil* and Card*, so new cards and sigils work without changing that code.
