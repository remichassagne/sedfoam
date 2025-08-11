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

#include "muEffModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::muEffModel> Foam::muEffModel::New
(
    const dictionary& ppDict,
    const phaseModel& phasea,
    const phaseModel& phaseb
)
{
    word muEffModelType
    (
        ppDict.getOrDefault<word>("muEffModel", "Coulomb")
    );

    Info << "Selecting muEffModel "
        << muEffModelType << endl;

    auto cstrIter =
        dictionaryConstructorTablePtr_->find(muEffModelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalError
            << "muEffModel::New(const dictionary&) : " << endl
            << "    unknown muEffModelType type "
            << muEffModelType
            << ", constructor not in hash table" << endl << endl
            << "    Valid muEffModel types are :"  << endl
            <<    dictionaryConstructorTablePtr_->sortedToc() << endl;
        Info << abort(FatalError) << endl;
    }

    return cstrIter()(ppDict, phasea, phaseb);
}


// ************************************************************************* //
