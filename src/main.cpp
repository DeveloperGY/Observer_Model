#include <vector>
#include <memory>
#include <iostream>

class IObserver
{
    private:

    public:

        virtual void update() = 0;
};

class ISubject
{
    protected:
        std::vector<IObserver *> observers;

        void notify()
        {
            for (auto &observer: this->observers)
            {
                observer->update();
            }
        }

    public:
        virtual void subscribe(IObserver *observer)
        {
            this->observers.push_back(observer);
            return;
        }
};

class WeatherStation: public ISubject
{
    private:
        bool raining;

    public:
        WeatherStation()
        {
            this->raining = false;
            return;
        }

        void set_raining(bool is_raining)
        {
            if (this->raining != is_raining)
            {
                this->raining = is_raining;
                this->notify();
            }

            return;
        }

        bool is_raining()
        {
            return this->raining;
        }
};

class WeatherReporter: public IObserver
{
    private:
        WeatherStation *station;

    public:
        WeatherReporter(WeatherStation *station)
        {
            this->station = station;

            station->subscribe(this);
            return;
        }

        void update() override
        {
            std::cout << "Is raining: " << this->station->is_raining() << "\n";
            return;
        }
};

int main(void)
{
    WeatherStation ws;
    WeatherReporter reporter(&ws);

    ws.set_raining(true);
    ws.set_raining(false);
    ws.set_raining(false);
    ws.set_raining(true);
    ws.set_raining(true);
    ws.set_raining(false);

    return 0;
}