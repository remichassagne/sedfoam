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

#include "Kamrin.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(Kamrin, 0);

    addToRunTimeSelectionTable
    (
        muEffModel,
        Kamrin,
        dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::Kamrin::Kamrin
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

    n
    (
        ppDict.getOrDefault
        (
            "n",
            dimensionedScalar("n",
                          dimensionSet(0, 0, 0, 0, 0, 0, 0),
                          4.0)
        )
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::Kamrin::~Kamrin()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField> Foam::Kamrin::muEff
(
    const volScalarField& pff_,
    const volScalarField& magDtensor_,
    const volScalarField& Theta_
) const
{
    Info << "Dsmall = " << Dsmall_ << endl;
    Info << "1./n - 1 = " << 1./n - 1 << endl;
    return (
        0.2*
        pow(phasea_.rho(), 1./(2*n) - 1./6.)*
        pow(phasea_.d(), 1./n)*
        pow(pff_, 7./6.-1/(2*n))*
        pow(sqrt(pow(magDtensor_,2) + pow(Dsmall_, 2)), 1./n - 1)*
        pow(Theta_, -1./6.)
    );
}

// ************************************************************************* //
