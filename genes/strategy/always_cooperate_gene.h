/*
 *  always_cooperate_gene.h
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to AlwaysCooperateGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_ALWAYS_COOPERATE_GENE_H
#define PG_PRIDIL_ALWAYS_COOPERATE_GENE_H

#include <string>

#include "../../pridil_common.h"
#include "../strategy_gene.h"

class Brain;

class AlwaysCooperateGene : public StrategyGene {
    public:
        explicit AlwaysCooperateGene(const Brain& brain) :
            StrategyGene(brain, always_cooperate) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

#endif      // PG_ALWAYS_COOPERATE_GENE_H
