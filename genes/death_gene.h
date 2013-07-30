/*
 *  death_gene.h
 *  ============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to DeathGene
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_DEATH_GENE_H
#define PG_PRIDIL_DEATH_GENE_H

#include <string>

#include "../pridil_common.h"
#include "gene.h"


namespace pridil {

class DeathGene : public Gene {
    public:
        explicit DeathGene(const Brain& brain,
                           const CreatureInit& c_init) :
            Gene(brain), m_life_expectancy(c_init.life_expectancy),
            m_life_expectancy_range(c_init.life_expectancy_range) {}
        virtual std::string name() const;
        bool is_dead(Day age) const;

    private:
        Day m_life_expectancy;
        Day m_life_expectancy_range;
};

}       //  namespace pridil

#endif      //  PG_PRIDIL_DEATH_GENE_H
