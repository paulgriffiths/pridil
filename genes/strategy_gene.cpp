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

using namespace pridil;


/*
 *  Returns a strategy gene's strategy.
 */

Strategy StrategyGene::strategy() const {
    return m_strategy;
}
