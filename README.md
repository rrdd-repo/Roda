# Roda

## Description
Game inspired by Wheel of Fortune developed in C.

Many of the answers were inside jokes from my college class so don't expect to get some of them. The game's answers can be changed with the *guessWords* and *guessHints* arrays though

First thing the game asks of you is how many rounds do you want to play. After you input the amount, the game will start.

The main UI shows the leaderboard of the game; whenever a player gets more money than someone above them, they’ll be moved up. Aside from that, there’s the phrase or word the players are guessing, with the tip related to it right above it.

The next screen shows the wheel and whatever will be of your fate. The wheel has 3 options, which are chosen at random:
- Assigns a random value that will be rewarded to the current player in case they get a letter right.
- Skips the current player’s turn and skips to the next.
- Bankrupts the current player and skips to the next.

If your roll is successful, you’ll be able to guess the letter for the word. The following rules apply:
- If you guess a vowel and get it right, you’ll get the amount of money requested, but the game will also skip your turn.
- If you guess a consonant and get it right, you’ll get the amount of money requested and keep your turn.
- If you guess the letter wrong, your turn will be skipped.
- If the letter is correctly guessed and appears multiple times in the word, the game will multiply the prize money accordingly.
The game ends when the amount of rounds requested ends. The top ranking player will also get a message congratulating them.

## Credits
- **Rosa de Souza**
- **Eduardo Krapas**