/*
 *  death_gene.cpp
 *  ==============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of DeathGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include "../pridil_common.h"
#include "death_gene.h"

using namespace pridil;


/*
 *  Returns true if the provided age exceeds life expectancy.
 */

bool DeathGene::is_dead(Day age) const {
    return (age > m_life_expectancy ? true : false);
}


/*
 *  Returns the name of the gene.
 */

std::string DeathGene::name() const {
    return "death gene";
}

