from collections import defaultdict
import enum
import typing

import matplotlib.pyplot as plt
import matplotlib.figure
import matplotlib.axes
import matplotlib.patches

from rich import print

import dataclasses


@dataclasses.dataclass(unsafe_hash=True)
class Location:
    x: int
    y: int


class Word:

    class Direction(enum.Enum):
        DOWN = enum.auto()
        RIGHT = enum.auto()

    def __init__(self, data: str, location: Location, direction: Direction) -> None:
        self._data = data
        self._location = location
        self._direction = direction

    @property
    def direction(self) -> Direction:
        return self._direction

    @property
    def word(self) -> str:
        return self._data

    @property
    def location(self) -> Location:
        return self._location

    def occupied_locations(self) -> set[Location]:
        match self._direction:
            case Word.Direction.DOWN:
                return {
                    Location(self._location.x, self.location.y + y)
                    for y in range(len(self._data))
                }

            case Word.Direction.RIGHT:
                return {
                    Location(self.location.x + x, self.location.y)
                    for x in range(len(self._data))
                }

    def __repr__(self) -> str:
        return f"Word({self._data}, {self._location}, {self.direction})"


def get_all_adjacent_locations(word: Word) -> set[Location]:
    all_locations: set[Location] = set()
    start_location = word.location

    match word.direction:
        case Word.Direction.DOWN:
            all_locations.add(Location(start_location.x, start_location.y - 1))

            all_locations.update(
                Location(start_location.x + 1, y)
                for y in range(start_location.y, len(word.word))
            )

            all_locations.update(
                Location(start_location.x - 1, y)
                for y in range(start_location.y, len(word.word))
            )

            all_locations.add(
                Location(start_location.x, start_location.y + len(word.word))
            )
        case Word.Direction.RIGHT:
            all_locations.add(Location(start_location.x - 1, start_location.y))

            all_locations.update(
                Location(x, start_location.y + 1)
                for x in range(start_location.x, len(word.word))
            )

            all_locations.update(
                Location(x, start_location.y - 1)
                for x in range(start_location.x, len(word.word))
            )

            all_locations.add(
                Location(start_location.x + len(word.word), start_location.y)
            )

    return all_locations


def render_word(word: Word, ax: matplotlib.axes.Axes) -> None:
    match word.direction:
        case Word.Direction.DOWN:
            for letter, y in zip(
                word.word, range(word.location.y, word.location.y + len(word.word))
            ):
                ax.text(word.location.x, y, letter, verticalalignment="top")
        case Word.Direction.RIGHT:
            for letter, x in zip(
                word.word, range(word.location.x, word.location.x + len(word.word))
            ):
                ax.text(x, word.location.y, letter, verticalalignment="top")


def render_words(
    words: typing.Iterable[Word],
    ax: matplotlib.axes.Axes,
) -> None:
    for word in words:
        render_word(word, ax)


def render_grid(xrange: list[int], yrange: list[int], ax: matplotlib.axes.Axes):
    ax.hlines(yrange, min(xrange), max(xrange), color="tab:grey")
    ax.vlines(xrange, min(yrange), max(yrange), color="tab:grey")


def highlight_locations(
    locations: typing.Iterable[Location],
    ax: matplotlib.axes.Axes,
    color: str = "yellow",
):
    for location in locations:
        ax.add_patch(
            matplotlib.patches.Rectangle(
                (location.x, location.y),
                1,
                1,
                color=color,
                alpha=0.5,
            )
        )


class Gamestate:
    def __init__(self):
        self._words: list[Word] = []
        self._word_occupied_locations: set[Location] = set()
        self._open_adjacent_locations: set[Location] = set()

    def add_word(self, word: Word):
        self._words.append(word)
        self._word_occupied_locations |= word.occupied_locations()
        self._open_adjacent_locations = (
            self._open_adjacent_locations
            | get_all_adjacent_locations(word) - self._word_occupied_locations
        )

    @property
    def words(self) -> list[Word]:
        return self._words

    def render(self, ax: matplotlib.axes.Axes):
        board_left_bound = (
            min(location.x for location in self._word_occupied_locations) - 10
        )
        board_right_bound = (
            max(location.x for location in self._word_occupied_locations) + 10
        )
        board_lower_bound = (
            min(location.y for location in self._word_occupied_locations) - 10
        )
        board_upper_bound = (
            max(location.y for location in self._word_occupied_locations) + 10
        )

        ax.set_xlim(board_left_bound, board_right_bound)
        ax.set_ylim(board_lower_bound, board_upper_bound)

        render_grid(
            list(range(board_left_bound, board_right_bound)),
            list(range(board_lower_bound, board_upper_bound)),
            ax,
        )

        highlight_locations(self._open_adjacent_locations, ax)
        highlight_locations(self._word_occupied_locations, ax, color="tab:green")
        render_words(self._words, ax)
        ax.set_aspect(1)
        ax.invert_yaxis()

    def _word_collides(self, word: Word, intended_collision: Location) -> bool:
        return any(
            loc in self._word_occupied_locations
            for loc in word.occupied_locations()
            if loc != intended_collision
        )

    @staticmethod
    def _get_word_origin_from_ith_letter(
        i: int, direction: Word.Direction, letter_location: Location
    ) -> Location:
        if direction == Word.Direction.DOWN:
            return Location(letter_location.x, letter_location.y - i)
        elif direction == Word.Direction.RIGHT:
            return Location(letter_location.x - i, letter_location.y)

    def get_valid_word_placements(self, valid_words: list[str]) -> list[Word]:
        valid_word_placements: list[Word] = []

        letter_to_loc_map: dict[str, list[Location]] = defaultdict(list)

        for word in self._words:
            for letter, loc in zip(word.word, word.occupied_locations()):
                letter_to_loc_map[letter].append(loc)

        for word in valid_words:
            for i, letter in enumerate(word):
                for dir in (Word.Direction.DOWN, Word.Direction.RIGHT):
                    locations_for_letter = letter_to_loc_map[letter]
                    for location in locations_for_letter:
                        attempted_placement = Word(
                            word,
                            Gamestate._get_word_origin_from_ith_letter(
                                i, dir, location
                            ),
                            dir,
                        )

                        if not self._word_collides(attempted_placement, location):
                            valid_word_placements.append(attempted_placement)

        return valid_word_placements


valid_words = ["HELLO", "EATERY"]

import copy


def main():
    game = Gamestate()

    game.add_word(Word("FOO", Location(0, 0), direction=Word.Direction.DOWN))

    potential_plays = game.get_valid_word_placements(valid_words)

    fig, axs = plt.subplots(1, len(potential_plays))
    print(potential_plays)

    axs: list[matplotlib.axes.Axes] = axs
    for ax, play in zip(axs, potential_plays):
        potential_game = copy.deepcopy(game)
        potential_game.add_word(play)

        potential_game.render(ax)

    plt.show()


if __name__ == "__main__":
    main()
