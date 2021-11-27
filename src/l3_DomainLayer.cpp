#include "hw/l3_DomainLayer.h"

using namespace std;

// bool Person::invariant() const
// {
//     return _year_of_birth >= MIN_YEAR_OF_BIRTH && _year_of_birth <= MAX_YEAR_OF_BIRTH && !_first_name.empty() && _first_name.size() <= MAX_NAME_LENGTH && !_last_name.empty() && _last_name.size() <= MAX_NAME_LENGTH;
// }

const string &Converter::toString(Fraction fraction_code)
{
    return fraction_to_string.find(fraction_code)->second;
}
const Fraction Converter::toFraction(const string &fraction)
{
    auto it = string_to_fraction.find(fraction);
    return it == string_to_fraction.end() ? FRACTION_UNKNOWN : it->second;
}

bool Candidate::invariant() const
{
    return _name.size() <= MAX_FIO_FIELD_LENGTH && _surname.size() <= MAX_FIO_FIELD_LENGTH && _age <= MAX_AGE && _age >= MIN_AGE && !_name.empty() && !_surname.empty();
}

// Person::Person(const std::string &first_name, const std::string &last_name, uint16_t year_of_birth)
//     : _first_name(first_name), _last_name(last_name), _year_of_birth(year_of_birth)
// {
//     assert(invariant());
// }

Candidate::Candidate(const string &name, const string &surname, uint age, uint income, Fraction fraction, uint voices)
    : _name(name), _surname(surname), _age(age), _income(income), _fraction(fraction), _voices(voices)
{
    assert(invariant());
}

Candidate::Candidate(const char *name, const char *surname, long unsigned int age, long unsigned int income, const char *fraction, long unsigned int voices)
{
    _name = string(name);
    _surname = string(surname);
    _age = age;
    _income = income;
    _fraction = Converter::toFraction(string(fraction));
    _voices = voices;
    assert(invariant());
}

// const string &Person::getFirstName() const
// {
//     return _first_name;
// }

// const string &Person::getLastName() const
// {
//     return _last_name;
// }

// uint16_t Person::getYearOfBirth() const
// {
//     return _year_of_birth;
// }

const string &Candidate::getName() const { return _name; }
const string &Candidate::getSurname() const { return _surname; }
const uint Candidate::getAge() const { return _age; }
const uint Candidate::getIncome() const { return _income; }
const Fraction Candidate::getFraction() const { return _fraction; }
const uint Candidate::getVoices() const { return _voices; }

// bool Person::write(ostream &os)
// {
//     writeString(os, _first_name);
//     writeString(os, _last_name);
//     writeNumber(os, _year_of_birth);

//     return os.good();
// }

bool Candidate::write(ostream &os)
{
    writeString(os, _name);
    writeString(os, _surname);
    writeNumber(os, _age);
    writeNumber(os, _income);
    writeString(os, Converter::toString(_fraction));
    writeNumber(os, _voices);

    return os.good();
}

// shared_ptr<ICollectable> ItemCollector::read(istream &is)
// {
//     string first_name = readString(is, MAX_NAME_LENGTH);
//     string last_name = readString(is, MAX_NAME_LENGTH);
//     uint16_t year = readNumber<uint16_t>(is);

//     return std::make_shared<Person>(first_name, last_name, year);
// }

shared_ptr<ICollectable> ItemCollector::read(istream &is)
{
    string name = readString(is, MAX_FIO_FIELD_LENGTH);
    string surname = readString(is, MAX_FIO_FIELD_LENGTH);
    uint age = readNumber<uint>(is);
    uint income = readNumber<uint>(is);
    Fraction fraction = Converter::toFraction(readString(is, MAX_FRACTION_LENGTH));
    uint voices = readNumber<uint>(is);

    return make_shared<Candidate>(name, surname, age, income, fraction, voices);
}
