/*---------------------------------------------------------------------------*\
Copyright (C) 2015 Cyrille Bonamy, Julien Chauchat, Tian-Jian Hsu
                   and contributors

License
    This file is part of SedFOAM.

    SedFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SedFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with SedFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::Coulomb

Description
    Chauchat, J., Guillou, S., Bang, D. P. V., and Nguyen, K. D. (2013).
    Modelling sedimentation–consolidation in the framework of a
    one-dimensional two-phase flow model. Journal of Hydraulic Research,
    51(3):293–305.

SourceFiles
    Coulomb.C

\*---------------------------------------------------------------------------*/

#ifndef Coulomb_H
#define Coulomb_H

#include "muEffModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class Coulomb Declaration
\*---------------------------------------------------------------------------*/

class Coulomb
:
    public muEffModel
{
private:
    //- minimum shear rate
    const dimensionedScalar Dsmall_;

    //- angle of internal friction
    const dimensionedScalar phi_;

public:

    //- Runtime type information
    TypeName("Coulomb");


    // Constructors

    //- Construct from components
    Coulomb
    (
        const dictionary& ppDict,
        const phaseModel& phasea,
        const phaseModel& phaseb
    );

    //- Destructor
    virtual ~Coulomb();

    // Member Functions

    tmp<volScalarField> muEff
    (
        const volScalarField& pff_,
        const volScalarField& magDtensor_,
        const volScalarField& Theta_
      ) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
