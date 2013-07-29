pridil
======

What is it?
-----------

**Pridil** is an iterated prisoner's dilemma evolution simulator inspired by
Robert Axelrod's "The Evolution of Cooperation" (1984) and the interest it
kindled.

The problem underlying the prisoner's dilemma was originally framed by Merrill
Flood and Melvin Dreshner in 1950, and refers to a situation where two parties,
in the absence of knowledge about the other party's intention, are motivated
not to cooperate with each other when following a rational self-interest,
even though both parties would benefit more by mutual cooperation.

The interest from an evolutionary perspective comes from examining how
individuals fare when they follow a pre-programmed strategy for interacting
within the "game", rather than following a rational self-interest. On the
grounds that cooperation is mutually beneficial but individually not rational,
and under the assumption that the benefits from any such cooperation may be
expected to result in reproductive success and the proliferation of genes
responsible for such a strategy, such an examination may shed light on how
a tendency to cooperate can be evolutionarily stable and successful despite
the fact that such a strategy may not be rational from an individual
perspective.

Refer to the [Wikipedia article on the subject]
(https://en.wikipedia.org/wiki/Prisoner's_dilemma) for more on the subject.

Who maintains it?
-----------------
**Pridil** is written and maintained by Paul Griffiths.

The latest version
------------------
Details of the latest version can be found on the GitHub project page at
<https://github.com/paulgriffiths/pridil>.

**Pridil** is still a work-in-progress. Currently, a number of strategies
are implemented and creatures and play against each other with an
observable effect on individual resources as a measure of success. Creatures
can die when they run out of resources or reach the end of their life
expectancy. Creatures can reproduce when they obtain a specified level
of resources through successfully playing games.

Planned future features include:
* Different geographical areas with an algorithm for movement, to allow
for initial populations of similar-strategy creatures, and the observation
of effects when individual creatures migrate to other areas.
* Random mutations of strategy when reproducing.

Documentation
-------------
Up-to-date documentation can be found at
<https://github.com/paulgriffiths/pridil/wiki>.

Installation
------------
**Pridil** is written in C++.

Download the source code and run `make` from the main directory. Invoking
`pridil -h` or `pridil --help` prints a help message showing usage and
options.

Licensing
---------
Please see the file called LICENSE.

Contacts
--------
* If you have a concrete bug report for **Pridil** please go to the GitHub
issue tracker at <https://github.com/paulgriffiths/pridil/issues>.
