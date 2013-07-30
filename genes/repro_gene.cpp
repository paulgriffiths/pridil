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
#include "repro_gene.h"

using namespace pridil;


/*
 *  Constructor.
 */

ReproGene::ReproGene(const Brain& brain, const CreatureInit& c_init) :
            Gene(brain), m_offspring_init(c_init) {
    m_offspring_init.starting_resources = c_init.repro_cost;            
}

/*
 *  Returns the name of the gene.
 */

std::string ReproGene::name() const {
    return "repro gene";
}


/*
 *  Returns an offspring
 */

Creature * ReproGene::reproduce(int& resources) const {
    Creature * new_creature = 0;

    if ( resources >= m_offspring_init.repro_min_resources ) {
        new_creature = new Creature(m_offspring_init);
        resources -= m_offspring_init.repro_cost;
    }

    return new_creature;
}
