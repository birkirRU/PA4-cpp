# PA4 - Inscryption style card game

Turn based card battle. You and enemy have 3 lanes. Place cards, then combat. Get enemy health to 0 to win.

## 1. User section

**Run:** `make` then `./game`

**Play:** You get 3 cards + 1 squirrel at start. Each turn you can draw (c = deck, s = squirrel), then place cards. Type `done` when you want to end your turn and do combat.

Cards have health, damage, and blood cost. To play a card with cost you need to sacrifice that many cards from your row (pick positions 0, 1, 2). You can place on an empty slot or on top of a card (that card counts as 1 sacrifice if it has cost).

Combat: your cards hit opposite lane, then enemy cards hit. Damage goes to the card there or to face if empty. If you kill a card the extra damage goes to face.

**Commands:** At start of turn type c or s. To place type hand number and position like `1 0`. Type `done` to end turn. When sacrificing type the positions e.g. `0 1`.

Sigils: Airborne = hard to block (need Mighty Leap to block). Fledgling = WolfCup becomes Wolf after one turn. Waterborne = blockable every other turn.

## 2. Programmer section

**Structure:** main starts the game, BattleManager runs the loop (init, then each turn: initializeTurn for draw/place, playTurn for combat and onTurnEnd). Board holds the 3 rows and does resolveCombat (targeting with sigils, then resolveAttack with overflow damage). Entity is base, Player and Enemy inherit. Card is base, Wolf/Raven/Bullfrog/GreatWhite/Squirrel/WolfCup inherit. Sigil is base, Airborne/MightyLeap/Waterborne/Fledgling inherit; SigilRegister gives you the right one by name. Deck has addCard<CardType> template and draw/discard/shuffle.

**Polymorphism:** Entity virtuals (drawCard, isDead, etc) so player and enemy can differ. Card pointers everywhere so we don't care which card type. Sigil pointers from getSigil so we call canBeBlockedBy/canBlock/onTurnEnd without knowing which sigil.

**Extend:** New card = new class from Card, add addCard<It> in constructors. New sigil = new SigilName, new class from Sigil, register it, add case in formatSigils if you want it shown. New entity = derive from Entity and wire it in.
