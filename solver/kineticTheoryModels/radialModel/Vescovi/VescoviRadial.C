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

#include "VescoviRadial.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(VescoviRadial, 0);

    addToRunTimeSelectionTable
    (
        radialModel,
        VescoviRadial,
        dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::VescoviRadial::VescoviRadial(const dictionary& dict)
:
    radialModel(dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::VescoviRadial::~VescoviRadial()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField> Foam::VescoviRadial::g0
(
    const volScalarField& alpha,
    const dimensionedScalar& alphaMax,
    const dimensionedScalar& muPart
) const
{
    return neg(alpha-0.49)*(2-alpha)/(2*pow(1-alpha, 3)) +
        pos(alpha-0.49)*(2-0.49)/(2*pow(1-0.49, 3))*(alphaMax-0.49) /
        (alphaMax-alpha);
}


Foam::tmp<Foam::volScalarField> Foam::VescoviRadial::g0prime
(
    const volScalarField& alpha,
    const dimensionedScalar& alphaMax,
    const dimensionedScalar& muPart
) const
{
    // modified by C.Z.
    return 1.0/sqr(1.0 - alpha)
         + (3.0*(1.0 - alpha) + 6.0*alpha)/(2.0*(1.0 - alpha))
         + (2.0*alpha*(1.0 - alpha) + 3.0*pow(alpha, 2))
          /(2.0*pow(1.0 - alpha, 4));
}


// ************************************************************************* //
