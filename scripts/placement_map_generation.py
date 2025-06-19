#!/home/jevndev/dev/external/english-words/.venv/bin/python3

import collections
import dataclasses
import enum
import functools
import typing
from rich import print


# +-----> +x
# |
# |
# v
# +y


class Direction(enum.Enum):
    DOWN = enum.auto()
    RIGHT = enum.auto()


@dataclasses.dataclass(unsafe_hash=True)
class ParentNode:
    word: str
    direction: Direction


Location: typing.TypeAlias = tuple[int, int]


@dataclasses.dataclass
class Node(ParentNode):
    relative_position: Location


def can_place_word(
    word: str, parent: ParentNode, location: Location, direction: Direction
) -> bool:
    parent_letter_locations: dict[Location, str] = {}

    if parent.direction == Direction.DOWN:
        for i, letter in enumerate(parent.word):
            parent_letter_locations[(0, i)] = letter
    else:
        for i, letter in enumerate(parent.word):
            parent_letter_locations[(i, 0)] = letter

    current_letter_location = location

    for i, letter in enumerate(word):
        if (
            current_letter_location in parent_letter_locations
            and parent_letter_locations[current_letter_location] != letter
        ):
            return False

        if direction == Direction.DOWN:
            current_letter_location: Location = (
                current_letter_location[0] + 0,
                current_letter_location[1] + 1,
            )
        else:
            current_letter_location: Location = (
                current_letter_location[0] + 1,
                current_letter_location[1] + 0,
            )

    return True


def get_placements_for_word(
    parent: ParentNode, wordList: typing.Sequence[str]
) -> list[Node]:
    all_nodes: list[Node] = []

    letter_to_position, position_to_letter = map_letters_to_positions(parent)

    for word in wordList:
        for direction in Direction.DOWN, Direction.RIGHT:
            for i, letter in enumerate(word):
                if letter in letter_to_position:
                    for x, y in letter_to_position[letter]:
                        if direction == Direction.DOWN:
                            word_origin = (x, y - i)
                        else:
                            word_origin = (x - i, y)
                        if not (
                            word == parent.word
                            and word_origin == (0, 0)
                            and direction == parent.direction
                        ):
                            all_nodes.append(Node(word, direction, word_origin))

    def can_place_node(node: Node) -> bool:
        x, y = node.relative_position
        for i, letter in enumerate(node.word):
            if node.direction == Direction.DOWN:
                l = x, y + i
            else:
                l = x + i, y

            if l in position_to_letter and position_to_letter[l] != letter:
                return False

        return True

    return [node for node in all_nodes if can_place_node(node)]


@functools.cache
def map_letters_to_positions(
    parent: ParentNode,
) -> tuple[dict[str, list[Location]], dict[Location, str]]:
    letter_to_position: dict[str, list[Location]] = collections.defaultdict(list)
    position_to_letter: dict[Location, str] = {}

    for i, letter in enumerate(parent.word):
        if parent.direction == Direction.DOWN:
            letter_to_position[letter].append((0, i))
            position_to_letter[(0, i)] = letter
        else:
            letter_to_position[letter].append((i, 0))
            position_to_letter[(i, 0)] = letter
    return letter_to_position, position_to_letter


def load_unique_words() -> set[str]:
    all_words = set()
    with open("words_alpha.txt", "r") as f:
        for line in f:
            all_words.add(line.strip("\n"))
    return all_words


def main():
    all_words = load_unique_words()

    word_graph = {}

    for direction in (Direction.DOWN, Direction.RIGHT):
        for word in all_words:
            parent = ParentNode(word, direction)

            word_graph[parent] = get_placements_for_word(parent, all_words)
            return

    print(word_graph)


if __name__ == "__main__":
    main()
