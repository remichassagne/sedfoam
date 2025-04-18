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

Class
    Foam::BerziRadial

Description
    \verbatim
    "Different singularities in the functions of extended kinetic theory at 
    the origin of the yield stress in granular flows"
    D. Berzi, D. Vescovi (2015).
    Physics of Fluids 27, 013302.
    \endverbatim

    This file is in the \dir kineticTheoryModels/radialModel/Berzi
    subdirectory inside the subdirectory
    \dir kineticTheoryModels/radialModel inside the directory
    \dir kineticTheoryModels

SourceFiles
    BerziRadial.C

\*---------------------------------------------------------------------------*/

#ifndef BerziRadial_H
#define BerziRadial_H

#include "radialModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class Berziradial Declaration
\*---------------------------------------------------------------------------*/

class BerziRadial
:
    public radialModel
{

public:

    //- Runtime type information
    TypeName("Berzi");


    // Constructors

        //- Construct from components
        BerziRadial(const dictionary& dict);


    //- Destructor
    virtual ~BerziRadial();


    // Member Functions


        tmp<volScalarField> g0
        (
            const volScalarField& alpha,
            const dimensionedScalar& alphaMax,
            const dimensionedScalar& muPart
        ) const;

        tmp<volScalarField> g0prime
        (
            const volScalarField& alpha,
            const dimensionedScalar& alphaMax,
            const dimensionedScalar& muPart
        ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
