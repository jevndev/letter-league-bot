import enum
import typing

import matplotlib.pyplot as plt
import matplotlib.figure
import matplotlib.axes
import matplotlib.patches

from rich import print

import dataclasses


@dataclasses.dataclass
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


def get_all_adjacent_locations(word: Word) -> list[Location]:
    all_locations: list[Location] = []
    start_location = word.location

    match word.direction:
        case Word.Direction.DOWN:
            all_locations.append(Location(start_location.x, start_location.y - 1))

            all_locations.extend(
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


def highlight_locations(locations: typing.Iterable[Location], ax: matplotlib.axes.Axes):
    for location in locations:
        ax.add_patch(
            matplotlib.patches.Rectangle(
                (location.x, location.y),
                1,
                1,
                color="yellow",
                alpha=0.5,
            )
        )


def main():
    words = [Word("Hello", Location(0, 0), Word.Direction.DOWN)]
    fig, ax = plt.subplots(1, 1)

    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)

    render_grid(list(range(-10, 10)), list(range(-10, 10)), ax)

    locations = get_all_adjacent_locations(words[0])
    print(locations)
    highlight_locations(locations, ax)

    render_words(words, ax)

    ax.invert_yaxis()
    ax.set_aspect(1)
    plt.show()


if __name__ == "__main__":
    main()
