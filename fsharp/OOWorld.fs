module OOWorld
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
        abstract member move: PointF -> string
        abstract member recharge: int32 -> string
    end

type Car(name, start, charge) = 
    inherit Robot(name, start, charge)
        override x.move direction = "We are going to go in 4 directions &, if there is another Robot, fight for our lives!"
        override x.recharge time = "In here we are rechargin our battery"

type Omni(name, start, charge, turPower: int32) = 
    inherit Car(name, start, charge)
        override x.move direction = "And here I am going to move in 8 directions!"
        override x.recharge time = "Same thing - we are recharching"
        member x.turret = turPower  //  Damn dis nigga has a turret!

type Boat(name, start, charge) = 
    inherit Robot(name, start, charge)
        override x.move direction = "Same thing as with car, but ON WATER YOU SICK NO I'M NOT"
        override x.recharge time = "We can recharge only if near dock station on water"

type Jet(name, start, charge) = 
    inherit Robot(name, start, charge)
        override x.move direction = "Here we are going in 3 directions which depends on our direction, but OMG BY 3 DAMN BLOCKS AND ON ANY AREA"
        override x.recharge time = "Recharge only while in hangar"

type Heli(name, start, charge) = 
    inherit Jet(name, start, charge)
        override x.move direction = "Move in 8 direction on any surface"
        override x.recharge time = "At any time in any place!"
