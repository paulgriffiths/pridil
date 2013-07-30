/*
 *  repro_gene.h
 *  ============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to ReproGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_REPRO_GENE_H
#define PG_PRIDIL_REPRO_GENE_H

#include <string>

#include "../pridil_common.h"
#include "gene.h"
#include "../creature.h"


namespace pridil {

class ReproGene : public Gene {
    public:
        explicit ReproGene(const Brain& brain, const CreatureInit& c_init);
        virtual std::string name() const;
        Creature * reproduce(int& resources) const;

    private:
        CreatureInit m_offspring_init;
};

}       //  namespace pridil

#endif      //  PG_PRIDIL_REPRO_GENE_H
