/*
 *  gene.h
 *  ======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Gene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_GENE_H
#define PG_PRIDIL_GENE_H

#include <string>

#include "../pridil_common.h"
#include "../brain_complex.h"


namespace pridil {


class Gene {
    public:
        explicit Gene(const Brain& brain) : m_brain(brain) {}
        virtual ~Gene() {}
        virtual std::string name() const = 0;

    protected:
        const Brain& m_brain;

    private:
        Gene(const Gene&);
        const Gene& operator=(const Gene&);
};


}       //  namespace pridil

#endif      //  PG_PRIDIL_GENE_H
