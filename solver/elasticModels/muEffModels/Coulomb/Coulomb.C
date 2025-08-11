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

\*---------------------------------------------------------------------------*/

#include "Coulomb.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(Coulomb, 0);

    addToRunTimeSelectionTable
    (
        muEffModel,
        Coulomb,
        dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::Coulomb::Coulomb
(
    const dictionary& ppDict,
    const phaseModel& phasea,
    const phaseModel& phaseb
)
:
    muEffModel(ppDict, phasea, phaseb),

    Dsmall_
    (
        ppDict.getOrDefault
        (
            "Dsmall",
            dimensionedScalar("Dsmall",
                dimensionSet(0, 0, -1, 0, 0, 0, 0),
                1e-6)
        )
    ),

    phi_
    (
        ppDict.getOrDefault
        (
            "phi",
            dimensionedScalar("phi",
                          dimensionSet(0, 0, 0, 0, 0, 0, 0),
                          32)
        )*M_PI/180.0 //32° angle of repose
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::Coulomb::~Coulomb()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField> Foam::Coulomb::muEff
(
    const volScalarField& pff_,
    const volScalarField& magDtensor_,
    const volScalarField& Theta_
) const
{

    return pff_*Foam::sin(phi_)/sqrt(pow(magDtensor_,2) + pow(Dsmall_, 2));
}

// ************************************************************************* //
