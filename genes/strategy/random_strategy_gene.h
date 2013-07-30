/*
 *  random_strategy_gene.h
 *  ======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to RandomStrategyGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_RANDOM_STRATEGY_GENE_H
#define PG_PRIDIL_RANDOM_STRATEGY_GENE_H

#include <string>

#include "../../pridil_common.h"
#include "../strategy_gene.h"

class RandomStrategyGene : public StrategyGene {
    public:
        explicit RandomStrategyGene(const Brain& brain) :
            StrategyGene(brain, random_strategy) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

#endif      // PG_PRIDIL_RANDOM_STRATEGY_GENE_H
