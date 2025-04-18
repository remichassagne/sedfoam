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
    Foam::SahaAlamViscosity

Description
    \verbatim
    "Normal stress differences, their origin and constitutive relations for
    a sheared granular fluid"
    Saha, S; Alam, M (2016)
    Journal of Fluid Mechanics. 795:549-580
    \endverbatim

    This file is in the \dir kineticTheoryModels/viscosityModel/SahaAlam
    subdirectory inside the subdirectory
    \dir kineticTheoryModels/viscosityModel inside the directory
    \dir kineticTheoryModels

SourceFiles
    SahaAlamViscosity.C

\*---------------------------------------------------------------------------*/

#ifndef SahaAlamViscosity_H
#define SahaAlamViscosity_H

#include "viscosityModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace kineticTheoryModels
{

/*---------------------------------------------------------------------------*\
                           Class SahaAlamViscosity Declaration
\*---------------------------------------------------------------------------*/

class SahaAlamViscosity
:
    public viscosityModel
{

public:

    //- Runtime type information
    TypeName("SahaAlam");


    // Constructors

        //- Construct from components
        SahaAlamViscosity(const dictionary& dict);


    //- Destructor
    virtual ~SahaAlamViscosity();


    // Member functions

        tmp<volScalarField> mua
        (
            const volScalarField& alpha,
            const volScalarField& Theta,
            const volScalarField& g0,
            const volScalarField& musalt,
            const volScalarField& K,
            const dimensionedScalar& rhoa,
            const dimensionedScalar& da,
            const dimensionedScalar& e
        ) const;

        tmp<volScalarField> lambda
        (
            const volScalarField& alpha,
            const volScalarField& Theta,
            const volScalarField& g0,
            const dimensionedScalar& rhoa,
            const dimensionedScalar& da,
            const dimensionedScalar& e
        ) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace kineticTheoryModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
