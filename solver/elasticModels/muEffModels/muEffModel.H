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
    Foam::muEffModel

Description

This file is in the \dir muEffModel directory.

SourceFiles
    muEffModel.C
    newPpModel.C

\*---------------------------------------------------------------------------*/

#ifndef muEffModel_H
#define muEffModel_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "dictionary.H"
#include "phaseModel.H"
#include "runTimeSelectionTables.H"

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class muEffModel Declaration
\*---------------------------------------------------------------------------*/

class muEffModel
{
protected:

    // Protected data

        const dictionary& ppDict_;
        const phaseModel& phasea_;
        const phaseModel& phaseb_;

public:

    //- Runtime type information
    TypeName("muEffModel");


    // Declare runtime construction

        declareRunTimeSelectionTable
        (
            autoPtr,
            muEffModel,
            dictionary,
            (
                const dictionary& ppDict,
                const phaseModel& phasea,
                const phaseModel& phaseb
            ),
            (ppDict, phasea, phaseb)
        );


    // Constructors

        muEffModel
        (
            const dictionary& ppDict,
            const phaseModel& phasea,
            const phaseModel& phaseb
        );


    //- Destructor
    virtual ~muEffModel();


    // Selectors

        static autoPtr<muEffModel> New
        (
            const dictionary& ppDict,
            const phaseModel& phasea,
            const phaseModel& phaseb
        );


    // Member Functions
    virtual tmp<volScalarField> muEff
    (
        const volScalarField& pff_,
        const volScalarField& magDtensor_,
        const volScalarField& Theta_
    ) const = 0;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
