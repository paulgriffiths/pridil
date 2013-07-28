/*
 *  dna.h
 *  =====
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to DNA class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_DNA_H
#define PG_PRIDIL_DNA_H

#include <string>

#include "pridil_types.h"
#include "game.h"


class Brain;

/*
 *  Gene classes
 */

class Gene {
    public:
        virtual ~Gene() {}
        virtual std::string name() const = 0;
};

class StrategyGene : public Gene {
    public:
        virtual GameMove get_game_move(const CreatureID opponent,
                                       GameInfoList& opponent_memory) = 0;
};

class TitForTatGene : public StrategyGene {
    public:
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent,
                                       GameInfoList& opponent_memory);
};

class TitForTwoTatsGene : public StrategyGene {
    public:
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent,
                                       GameInfoList& opponent_memory);
};

class SuspTitForTatGene : public StrategyGene {
    public:
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent,
                                       GameInfoList& opponent_memory);
};

class NaiveProberGene : public StrategyGene {
    private:
        const double m_prob_random_defect;

    public:
        NaiveProberGene() : m_prob_random_defect(0.2) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent,
                                       GameInfoList& opponent_memory);
};

class RandomStrategyGene : public StrategyGene {
    public:
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent,
                                       GameInfoList& opponent_memory);
};

class AlwaysCooperateGene : public StrategyGene {
    public:
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent,
                                       GameInfoList& opponent_memory);
};

class AlwaysDefectGene : public StrategyGene {
    public:
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent,
                                       GameInfoList& opponent_memory);
};



/*
 *  DNA class
 */

class DNA {
    public:

        //  Constructor and destructor

        explicit DNA(const Brain& brain, Strategy strategy);
        ~DNA();

        //  Getter method

        const std::string strategy() const;

        //  Genetic action methods

        GameMove get_game_move(const CreatureID opponent,
                               GameInfoList& opponent_memory);


    private:
        const Brain& m_brain;
        StrategyGene * m_strategy_gene;

        DNA(const DNA&);                // Prevent copying
        DNA& operator=(const DNA&);     // Prevent assignment

};

#endif      // PG_PRIDIL_DNA_H
