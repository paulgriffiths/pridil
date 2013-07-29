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
        explicit Gene(const Brain& brain) : m_brain(brain) {}
        virtual ~Gene() {}
        virtual std::string name() const = 0;

    protected:
        const Brain& m_brain;

    private:
        Gene(const Gene&);
        const Gene& operator=(const Gene&);
};

class StrategyGene : public Gene {
    public:
        explicit StrategyGene(const Brain& brain,
                              const Strategy strategy) :
            Gene(brain), m_strategy(strategy) {}
        virtual GameMove get_game_move(const CreatureID opponent) const = 0;
        virtual Strategy strategy() const;

    private:
        Strategy m_strategy;
};

class TitForTatGene : public StrategyGene {
    public:
        explicit TitForTatGene(const Brain& brain) :
            StrategyGene(brain, tit_for_tat) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

class TitForTwoTatsGene : public StrategyGene {
    public:
        explicit TitForTwoTatsGene(const Brain& brain) :
            StrategyGene(brain, tit_for_two_tats) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

class SuspTitForTatGene : public StrategyGene {
    public:
        explicit SuspTitForTatGene(const Brain& brain) :
            StrategyGene(brain, susp_tit_for_tat) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

class NaiveProberGene : public StrategyGene {
    private:
        const double m_prob_random_defect;

    public:
        explicit NaiveProberGene(const Brain& brain) :
            StrategyGene(brain, naive_prober),
            m_prob_random_defect(0.2) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

class RandomStrategyGene : public StrategyGene {
    public:
        explicit RandomStrategyGene(const Brain& brain) :
            StrategyGene(brain, random_strategy) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

class AlwaysCooperateGene : public StrategyGene {
    public:
        explicit AlwaysCooperateGene(const Brain& brain) :
            StrategyGene(brain, always_cooperate) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

class AlwaysDefectGene : public StrategyGene {
    public:
        explicit AlwaysDefectGene(const Brain& brain) :
            StrategyGene(brain, always_defect) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};



/*
 *  DNA class
 */

class DNA {
    public:

        //  Constructor and destructor

        explicit DNA(const Brain& brain, const Strategy strategy);
        ~DNA();

        //  Getter methods

        const std::string strategy() const;
        Strategy strategy_value() const;

        //  Genetic action methods

        GameMove get_game_move(const CreatureID opponent) const;


    private:
        const Brain& m_brain;
        StrategyGene * m_strategy_gene;

        DNA(const DNA&);                // Prevent copying
        DNA& operator=(const DNA&);     // Prevent assignment

};

#endif      // PG_PRIDIL_DNA_H
