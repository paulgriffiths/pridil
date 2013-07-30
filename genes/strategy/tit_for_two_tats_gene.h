/*
 *  tit_for_two_tats_gene.h
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to TitForTwoTatsGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_TIT_FOR_TWO_TATS_GENE_H
#define PG_PRIDIL_TIT_FOR_TWO_TATS_GENE_H

#include <string>

#include "../../pridil_common.h"
#include "../strategy_gene.h"

class TitForTwoTatsGene : public StrategyGene {
    public:
        explicit TitForTwoTatsGene(const Brain& brain) :
            StrategyGene(brain, tit_for_two_tats) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

#endif      // PG_PRIDIL_TIT_FOR_TWO_TATS_GENE_H
