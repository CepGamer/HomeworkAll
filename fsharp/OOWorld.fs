open System.Drawing

type Terrain = Water | Earth | Mountains

[<AbstractClass>]
type Robot(name: string, start: PointF, batteryCharge: int32) = 
    class
        inherit obj()
        member x.charge = batteryCharge
        member x.name = name
        member x.pos = start
        member x.toString() = "No string fo' robots!"
        member x.pauseTime = 0
        abstract member move: PointF -> bool
        abstract member recharge: int32 -> unit
    end

type Car(name, start, charge) = 
    inherit Robot(name, start, charge)
        override x.move point = 
            
            true
        override x.recharge time = 
            x.pauseTime = time |> ignore

type Omni(name, start, charge) = 
    inherit Car(name, start, charge)

type Boat(name, start, charge) = 
    inherit Robot(name, start, charge)
        override x.move point = 
            true

        override x.recharge time = 
            ()

[<AbstractClass>]
type Fly(name, start, charge) = 
    inherit Robot(name, start, charge)
        

(*        abstract BatteryCharge: int32 with get
        abstract MaxBattery: int32 with get*)
