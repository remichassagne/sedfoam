/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
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
    Foam::RASModels::twophasekEpsilon

Group
    grpRASTurbulence

Description
    k-epsilon turbulence model for incompressible two phase flows.

    Reference:
    \verbatim
        Original model:
            Launder, B. E., & Spalding, D. B. (1972).
            Lectures in mathematical models of turbulence.

            Launder, B. E., & Spalding, D. B. (1974).
            The numerical computation of turbulent flows.
            Computer methods in applied mechanics and engineering,
            3(2), 269-289.

        Two-phase adaptation
            Hsu, T.-J., Jenkins, J. T., and Liu, P. L.-F. (2004).
            On two-phase sediment transport: sheet flow of massive particles.
            Proceedings of the Royal Society London A, 460, 2223-2250.

            Yu, X., Hsu, T.-J., and Hanes, D. M. (2010).
            Sediment transport under wave groups: Relative importance between
            nonlinear waveshape and nonlinear boundary layer streaming.
            Journal of Geophysical Research, 115, C02013.
    \endverbatim

    The default model coefficients correspond to the following:
    \verbatim
        twophasekEpsilonCoeffs
        {
            Cmu         0.09;
            C1          1.44;
            C2          1.92;
            C3ep        1.2;
            C4ep        1.0;
            alphak      1.0;
            alphaEps    1.3;
            KE2         1.0;
            KE4         1.0;
        }
    \endverbatim

    This file is in the \dir turbulenceModels/RAS/twophasekEpsilon subdirectory
    inside the \dir turbulenceModels/RAS subdirectory
    inside the \dir turbulenceModels subdirectory

SourceFiles
    twophasekEpsilon.C

\*---------------------------------------------------------------------------*/

#ifndef twophasekEpsilon_H
#define twophasekEpsilon_H

#include "RASModel.H"
#include "eddyViscosity.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RASModels
{

/*---------------------------------------------------------------------------*\
                           Class twophasekEpsilon Declaration
\*---------------------------------------------------------------------------*/

template<class BasicTurbulenceModel>
class twophasekEpsilon
:
    public eddyViscosity<RASModel<BasicTurbulenceModel>>
{
    // Private Member Functions

        // Disallow default bitwise copy construct and assignment
        twophasekEpsilon(const twophasekEpsilon&);
        void operator=(const twophasekEpsilon&);


protected:

    // Protected data

        // Model coefficients

            dimensionedScalar C3ep_;
            dimensionedScalar C4ep_;
            dimensionedScalar KE2_;
            dimensionedScalar KE4_;

            dimensionedScalar Cmu_;
            dimensionedScalar C1_;
            dimensionedScalar C2_;
            dimensionedScalar nutMax_;
            dimensionedScalar alphak_;
            dimensionedScalar alphaEps_;

         // two phase information
            const volScalarField& tmfexp_;
            const volScalarField& ESD3_;
            const volScalarField& ESD4_;
            const volScalarField& ESD5_;
            const volScalarField& ESD_;

        // Fields
            volScalarField k_;
            volScalarField epsilon_;

    // Protected Member Functions
        virtual void correctNut();


public:

    typedef typename BasicTurbulenceModel::alphaField alphaField;
    typedef typename BasicTurbulenceModel::rhoField rhoField;
    typedef typename BasicTurbulenceModel::transportModel transportModel;


    //- Runtime type information
    TypeName("twophasekEpsilon");

    // Constructors

        //- Construct from components
        twophasekEpsilon
        (
            const alphaField& alpha,
            const rhoField& rho,
            const volVectorField& U,
            const surfaceScalarField& alphaRhoPhi,
            const surfaceScalarField& phi,
            const transportModel& transport,
            const word& propertiesName = turbulenceModel::propertiesName,
            const word& type = typeName
        );


    //- Destructor
    #if (OFVERSION < 220 and OFVERSION >= 200) or OFVERSION == 00
        virtual ~twophasekEpsilon() = default;
    #else
        virtual ~twophasekEpsilon()
        {}
    #endif


    // Member Functions

        //- Read RASProperties dictionary
        virtual bool read();

        //- Return the effective diffusivity for k
        tmp<volScalarField> DkEff() const
        {
            return tmp<volScalarField>
            (
                new volScalarField("DkEff", this->nut_ + this->nu())
            );
        }

        //- Return the effective diffusivity for epsilon
        tmp<volScalarField> DepsilonEff() const
        {
            return tmp<volScalarField>
            (
                new volScalarField
                (
                    "DepsilonEff", this->nut_/alphaEps_ + this->nu()
                )
            );
        }

        //- Return the turbulence kinetic energy
        virtual tmp<volScalarField> k() const
        {
            return k_;
        }

        //- Return the turbulence kinetic energy dissipation rate
        virtual tmp<volScalarField> epsilon() const
        {
            return epsilon_;
        }
        virtual tmp<volScalarField> omega() const
        {
            return tmp<volScalarField>
            (
                new volScalarField
                (
                    IOobject
                    (
                        "omega",
                        this->mesh_.time().timeName(),
                        this->mesh_
                    ),
                    epsilon_/(Cmu_*k_),
                    epsilon_.boundaryField().types()
                )
            );
        }
        virtual tmp<volScalarField> tmf() const
        {
            return Foam::exp(Cmu_*tmfexp_*omega());
        }

        virtual tmp<volScalarField> ESD2() const
        {
            return ESD3_*(1.0-tmf());
        }

        //- Solve the turbulence equations and correct the turbulence viscosity
        virtual void correct();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RASModels
} // End namespace Foam


#ifdef NoRepository
    #include "twophasekEpsilon.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
