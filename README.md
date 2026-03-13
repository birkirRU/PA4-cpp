# PA4 – Inscryption-style JRPG

A turn-based card battle game inspired by Inscryption. You and an enemy take turns placing cards on a 3-lane board, then combat is resolved. Reduce the enemy’s health to zero to win.

---

## 1. User section

### How to run

```bash
make
./game
```

### How to play

- **Goal:** Reduce the enemy’s health to 0. You lose if your health reaches 0.
- You and the enemy each have a **row of 3 positions** (0, 1, 2). Cards placed there attack the opposite row each turn.
- You start with **3 cards from your deck + 1 Squirrel**. Each turn you may **draw** (deck or squirrel), **place cards**, then type **done** to end your turn and resolve combat.

### Game mechanics

- **Stats:** Each card has **health** (HP), **damage** (attack), and **blood cost** (how many of your own cards you must sacrifice to play it). Display format: `[Name health/damage C:cost S:sigils]`.
- **Placing cards:** When prompted, enter **hand number** (1–N) and **position** (0, 1, or 2). You can place on an **empty** slot or **on an occupied** slot: with cost 0 you replace the card; with cost ≥ 1 the card in that slot counts as one sacrifice.
- **Sacrifice:** Playing a card with blood cost requires sacrificing that many cards from your row. You are prompted to enter that many **positions** (0, 1, 2). The card in the slot you’re placing on can count as one of them.
- **Combat:** After you type **done**, your cards attack (by lane), then the enemy’s cards attack. Damage goes to the opposing card in the same lane; **overflow** damage (when the card is killed) goes to the opponent’s health. If a lane has no blocker, all damage goes to the opponent’s health.
- **Sigils:** Cards can have special abilities (e.g. **Airborne** – hard to block; **Mighty Leap** – can block Airborne; **Waterborne** – blockable only on certain turns; **Fledgling** – gains stats once at end of turn, then loses the sigil).

### Available commands

| When            | Input              | Meaning                                      |
|-----------------|--------------------|----------------------------------------------|
| Start of turn   | `c` or `s`         | Draw from **c**ard deck or **s**quirrel      |
| During turn     | `1 0` … `N 2`      | Place card **1**–**N** in position **0/1/2** |
| During turn     | `done`             | End your turn and resolve combat             |
| Sacrifice prompt| `0` or `0 1` etc.  | Positions to sacrifice (one per blood cost)  |

---

## 2. Programmer section

### Code design and architecture

- **Entry / game loop:** `main.cpp` runs the game; `BattleManager` (in `system/`) runs the battle loop: `initBattle()` → per turn `initializeTurn()` (draw, place cards) and `playTurn()` (resolve combat, turn end).
- **Board:** `Board` holds the three rows (player, enemy active, enemy pre), runs combat (`resolveCombat`, `resolveTargeting`, `resolveAttack`), applies damage and overflow, and calls `onTurnEnd()` for sigils.
- **Entities:** `Entity` is the base class (health, id, hand, deck). `Player` and `Enemy` derive from it; `Player` adds squirrel drawing, card placement with sacrifice, and input handling. Both use the same deck/card types but different turn logic.
- **Cards:** Base class `Card` (name, health, damage, bloodCost, sigils, isBase). Concrete types (`Wolf`, `Raven`, `Bullfrog`, `GreatWhite`, `Squirrel`, `WolfCup`) are derived and define stats and sigils. Cards are owned by `Deck` (unique_ptr); hands and board hold raw pointers.
- **Sigils:** Abstract `Sigil` with virtuals `canBeBlockedBy`, `canBlock`, `onAttack`, `onBlock`, `onTurnEnd`. Concrete sigils (`AirborneSigil`, `MightyLeapSigil`, `WaterborneSigil`, `FledglingSigil`) are registered in `SigilRegister`. The board looks up sigils by `SigilName` when resolving targeting and combat.
- **Deck:** Owns cards, maintains draw pile and discard; `addCard<CardType>()` is a template for adding card types. Draw/discard/shuffle and `random_card_max_blood` drive enemy card choice.

### Polymorphism and abstraction

- **Inheritance (entities):** `Entity` → `Player`, `Enemy`. Virtual methods: `shuffleDeck`, `drawStartingHand`, `drawCard`, `isDead`. The battle loop uses `Player` and `Enemy` through the same interface where appropriate (e.g. drawing, deck access).
- **Inheritance (cards):** `Card` → `Wolf`, `Raven`, `Bullfrog`, `GreatWhite`, `Squirrel`, `WolfCup`. Different types have different stats and sigils; combat and UI use the base `Card` pointer.
- **Inheritance (sigils):** `Sigil` → `AirborneSigil`, `MightyLeapSigil`, `WaterborneSigil`, `FledglingSigil`. The board calls `getSigil(SigilName)` and uses the returned `Sigil*` for targeting and turn-end behaviour, so new sigils can be added without changing combat code.
- **Templates:** `Deck::addCard<CardType>()` instantiates card types at compile time; entity constructors use it to build decks.

### How to extend the game

- **New card type:** Add a class derived from `Card` (e.g. in `card.h`/`card.cpp`), give it stats and sigils, and add `deckObj.addCard<NewCard>()` in `Player` and/or `Enemy` constructors.
- **New sigil:** Add a `SigilName` enum value, a class derived from `Sigil` implementing the desired virtuals, register it in `SigilRegister`, and handle it in `formatSigils` / display if needed. Combat and `onTurnEnd` already iterate over sigils, so behaviour is picked up automatically.
- **New entity type:** Derive from `Entity` (or from `Player`/`Enemy` if appropriate), override virtuals, and plug the new type into the battle setup if you want it to participate in the loop.
- **New actions or rules:** Extend `BattleManager` (e.g. extra phases), `Board` (e.g. new combat or placement rules), or add new `Sigil` callbacks and call them from the board where appropriate.

---

## Build and clean

```bash
make
./game

make clean  # remove executable and debug artifacts
```
