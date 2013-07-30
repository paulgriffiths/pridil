/*
 *  susp_tit_for_tat_gene.h
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to SuspiciousTitForTatGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_SUSP_TIT_FOR_TAT_GENE_H
#define PG_PRIDIL_SUSP_TIT_FOR_TAT_GENE_H

#include <string>
#include "../../pridil_common.h"
#include "../strategy_gene.h"


namespace pridil {


class SuspTitForTatGene : public StrategyGene {
    public:
        explicit SuspTitForTatGene(const Brain& brain) :
            StrategyGene(brain, susp_tit_for_tat) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};


}       //  namespace pridil

#endif      // PG_PRIDIL_SUSP_TIT_FOR_TAT_GENE_H
