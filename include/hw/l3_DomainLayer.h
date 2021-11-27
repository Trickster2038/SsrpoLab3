#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"
#include <map>

// const size_t MAX_NAME_LENGTH = 50;
// const size_t MIN_YEAR_OF_BIRTH = 1900;
// const size_t MAX_YEAR_OF_BIRTH = 2019;

const size_t MAX_FIO_FIELD_LENGTH = 30;
const size_t MAX_FRACTION_LENGTH = 20;
const uint MIN_AGE = 21;
const uint MAX_AGE = 120;

// class Person : public ICollectable
// {
//     std::string _first_name;
//     std::string _last_name;
//     uint16_t _year_of_birth;

// protected:
//     bool invariant() const;

// public:
//     Person() = delete;
//     Person(const Person &p) = delete;

//     Person &operator=(const Person &p) = delete;

//     Person(const std::string &first_name, const std::string &last_name, uint16_t year_of_birth);

//     const std::string &getFirstName() const;
//     const std::string &getLastName() const;
//     uint16_t getYearOfBirth() const;

//     virtual bool write(std::ostream &os) override;
// };

enum Fraction
{
    FRACTION_EDRO,
    FRACTION_YABLOKO,
    FRACTION_LDPR,
    FRACTION_NOVYE_LUDI,
    FRACTION_KPRF,
    FRACTION_UNKNOWN
};

class Candidate : public ICollectable
{
    std::string _name;
    std::string _surname;
    uint _age;
    uint _income;
    Fraction _fraction;
    uint _voices;

protected:
    bool invariant() const;

public:
    Candidate() = delete;
    Candidate(const Candidate &p) = delete;

    Candidate &operator=(const Candidate &p) = delete;
    Candidate(const std::string &name, const std::string &surname, uint age, uint income, Fraction fraction, uint voices);
    Candidate(const char *name, const char *surname, long unsigned int age, long unsigned int income, const char *fraction, long unsigned int voices);

    const std::string &getName() const;
    const std::string &getSurname() const;
    const uint getAge() const;
    const uint getIncome() const;
    const Fraction getFraction() const;
    const uint getVoices() const;

    virtual bool write(std::ostream &os) override;
};

class Converter
{
private:
    static inline std::map<Fraction, std::string> fraction_to_string = {{FRACTION_EDRO, "EDRO"},
                                                              {FRACTION_YABLOKO, "YABLOKO"},
                                                              {FRACTION_LDPR, "LDPR"},
                                                              {FRACTION_NOVYE_LUDI, "NOVIE LUDI"},
                                                              {FRACTION_KPRF, "KPRF"}};

    static inline std::map<std::string, Fraction> string_to_fraction = {{"EDRO", FRACTION_EDRO},
                                                              {"YABLOKO", FRACTION_YABLOKO},
                                                              {"LDPR", FRACTION_LDPR},
                                                              {"NOVIE LUDI", FRACTION_NOVYE_LUDI},
                                                              {"KPRF", FRACTION_KPRF}};

public:
    static const std::string &toString(Fraction fraction_code);
    static const Fraction toFraction(const std::string &fraction);
};

class ItemCollector : public ACollector
{
public:
    virtual std::shared_ptr<ICollectable> read(std::istream &is) override;
};

#endif // HW_L3_DOMAIN_LAYER_H
