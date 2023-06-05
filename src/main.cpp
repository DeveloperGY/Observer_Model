#include <vector>
#include <iostream>

class IObserver
{
    private:

    public:
        virtual void notify() = 0;
};

class ISubject
{
    private:
        std::vector<IObserver *> observers;

    protected:
        void _update()
        {
            for (auto &observer: this->observers)
            {
                observer->notify();
            }

            return;
        }
    
    public:
        void subscribe(IObserver *observer)
        {
            this->observers.push_back(observer);
        }
};

class WeatherSubject: public ISubject
{
    private:
        bool raining;
        float rain_depth;
        bool snowing;
        float snow_depth;

    public:
        WeatherSubject()
        {
            this->raining = false;
            this->rain_depth = 0.00f;
            this->snowing = false;
            this->snow_depth = 0.00f;

            return;
        }

        bool is_raining()
        {
            return this->raining;
        }

        bool is_snowing()
        {
            return this->snowing;
        }

        float get_rain_depth()
        {
            return this->rain_depth;
        }

        float get_snow_depth()
        {
            return this->snow_depth;
        }

        void set_raining(bool is_raining, float depth)
        {
            if (this->raining != is_raining || this->rain_depth != depth)
            {
                this->raining = is_raining;
                this->rain_depth = (this->is_raining()) ? depth : 0;
                this->_update();
            }
            return;
        }

        void set_snowing(bool is_snowing, float depth)
        {
            if (this->snowing != is_snowing || this->snow_depth != depth)
            {
                this->snowing = is_snowing;
                this->snow_depth = (this->is_snowing()) ? depth : 0;
                this->_update();
            }
            return;
        }
};

class WeatherObserver: public IObserver
{
    private:
        WeatherSubject *weather_subject;
        int id;

    public:
        WeatherObserver(WeatherSubject *weather_subject, int id)
        {
            this->weather_subject = weather_subject;
            weather_subject->subscribe(this);
            this->id = id;
            return;
        }

        void notify() override
        {
            std::cout << "\nWEATHER UPDATE " << this->id
                      << "\n-------------------"
                      << "\nIs Raining: " << weather_subject->is_raining()
                      << "\n    Estimated Depth: " << weather_subject->get_rain_depth() << " inches"
                      << "\n"
                      << "\nIs Snowing: " << weather_subject->is_snowing()
                      << "\n    Estimated Depth: " << weather_subject->get_snow_depth() << " inches"
                      << "\n\n";
            return;
        }
};

int main(void)
{
    // Weather Subject is akin to a weather station
    // Weather Observer is akin to a weather reporter

    WeatherSubject subject;

    WeatherObserver observer_0(&subject, 0);
    WeatherObserver observer_1(&subject, 1);
    WeatherObserver observer_2(&subject, 2);
    WeatherObserver observer_3(&subject, 3);

    subject.set_raining(true, 5);
    subject.set_raining(false, 0);
    subject.set_raining(false, 4.36);
    subject.set_raining(true, 2.73);
    subject.set_snowing(true, 9.63);

    return 0;
}