/*
 *  naive_prober.h
 *  ==============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to NaiveProberGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_NAIVE_PROBER_GENE_H
#define PG_PRIDIL_NAIVE_PROBER_GENE_H

#include <string>
#include "../../pridil_common.h"
#include "../strategy_gene.h"


namespace pridil {


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


}       //  namespace pridil

#endif      // PG_PRIDIL_NAIVE_PROBER_GENE_H
