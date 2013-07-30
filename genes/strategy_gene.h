/*
 *  strategy_gene.h
 *  ===============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to StrategyGene
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_STRATEGY_GENE_H
#define PG_PRIDIL_STRATEGY_GENE_H

#include <string>

#include "../pridil_common.h"
#include "gene.h"


namespace pridil {


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


}       //  namespace pridil

#endif      //  PG_PRIDIL_STRATEGY_GENE_H
