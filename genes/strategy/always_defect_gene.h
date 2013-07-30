/*
 *  always_defect_gene.h
 *  ====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to AlwaysDefectGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_ALWAYS_DEFECT_GENE_H
#define PG_PRIDIL_ALWAYS_DEFECT_GENE_H

#include <string>

#include "../../pridil_common.h"
#include "../strategy_gene.h"

class AlwaysDefectGene : public StrategyGene {
    public:
        explicit AlwaysDefectGene(const Brain& brain) :
            StrategyGene(brain, always_defect) {}
        virtual std::string name() const;
        virtual GameMove get_game_move(const CreatureID opponent) const;
};

#endif      // PG_PRIDIL_ALWAYS_DEFECT_GENE_H
