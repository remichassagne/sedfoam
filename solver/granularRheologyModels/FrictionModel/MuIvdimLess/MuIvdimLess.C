/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "MuIvdimLess.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace granularRheologyModels
{
    defineTypeNameAndDebug(MuIvdimLess, 0);
    addToRunTimeSelectionTable(FrictionModel, MuIvdimLess, dictionary);
}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::granularRheologyModels::MuIvdimLess::MuIvdimLess(const dictionary& dict)
:
    FrictionModel(dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::granularRheologyModels::MuIvdimLess::~MuIvdimLess()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField> Foam::granularRheologyModels::MuIvdimLess::muI
(
    const dimensionedScalar& mus,
    const dimensionedScalar& mu2,
    const dimensionedScalar& I0,
    const volScalarField& pa,
    const dimensionedScalar& rhoa,
    const dimensionedScalar& da,
    const dimensionedScalar& rhob,
    const dimensionedScalar& nub,
    const volScalarField& magD,
    const dimensionedScalar& Dsmall
) const
{
    return mus + (mu2 - mus)*magD/(I0*rhoa/rhob*da*pa/nub + magD + Dsmall);
}


Foam::tmp<Foam::volScalarField> Foam::granularRheologyModels::MuIvdimLess::I
(
    const volScalarField& pa,
    const dimensionedScalar& rhoa,
    const dimensionedScalar& da,
    const dimensionedScalar& rhob,
    const dimensionedScalar& nub,
    const volScalarField& magD
) const
{
    return rhob*nub*magD / (rhoa*da*pa);
}

// ************************************************************************* //
