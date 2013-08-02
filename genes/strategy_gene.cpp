/*
 *  strategy_gene.cpp
 *  =================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of StrategyGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include "../pridil_common.h"
#include "strategy_gene.h"
#include "strategy/strategy_genes.h"

using namespace pridil;


/*
 *  Returns a strategy gene's strategy.
 */

Strategy StrategyGene::strategy() const {
    return m_strategy;
}


/*
 *  Creates and returns a new StrategyGene based on the strategy
 *  contained in the provided CreatureInit struct.
 */

StrategyGene* pridil::StrategyGeneFactory(const Brain& brain,
                                          const CreatureInit& c_init) {
    StrategyGene* new_gene;

    switch ( c_init.strategy ) {
        case tit_for_tat:
            new_gene = new TitForTatGene(brain);
            break;
        case tit_for_two_tats:
            new_gene = new TitForTwoTatsGene(brain);
            break;
        case susp_tit_for_tat:
            new_gene = new SuspTitForTatGene(brain);
            break;
        case naive_prober:
            new_gene = new NaiveProberGene(brain);
            break;
        case random_strategy:
            new_gene = new RandomStrategyGene(brain);
            break;
        case always_cooperate:
            new_gene = new AlwaysCooperateGene(brain);
            break;
        case always_defect:
            new_gene = new AlwaysDefectGene(brain);
            break;
        default:
            throw UnknownStrategy();
     }

    return new_gene;
}
