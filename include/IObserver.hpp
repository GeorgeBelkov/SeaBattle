// Observer


class IObserver {
protected:
    IObserver() = default;
public:
    virtual ~IObserver() = default;
    virtual void Update() = 0;
};


// Subject


class Subject {
protected:
    Subject() = default; 
public:
    virtual ~Subject() = default;
    virtual void Notify() = 0;
    virtual void Append(IObserver*) = 0;
    virtual void Remove(IObserver*) = 0;
};