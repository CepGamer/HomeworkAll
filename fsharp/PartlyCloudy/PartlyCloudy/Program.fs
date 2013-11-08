module main
open System
open FsUnit
open NUnit.Framework

type CreatureType = Balloon | Bat | Bearcub | Hedgehog | Kitten | Piglet | Puppy

type DaylightType = Morning | Noon | Evening | Night

type LuminaryType = Shining | NotShining

type WindType = NoWind | WeakWind | Breathe | Hurricane

let gen = new Random()

[<Interface>]
type ILuminary = 
    abstract member IsShining: unit -> bool

[<Interface>]
type IDayLight = 
    abstract member Current: DaylightType

[<Interface>]
type IWind = 
    abstract member Current: WindType

[<Interface>]
type IWeatherFactory = 
    abstract member createDaylight: unit -> IDayLight
    abstract member createLuminary: unit -> ILuminary
    abstract member createWind: unit -> IWind

[<Interface>]
type IMagic = 
    abstract member CallStork: CreatureType -> unit
    abstract member CallDaemon: CreatureType -> unit

type Daylight () = 
    interface IDayLight with
        member this.Current = 
            match gen.Next 4 with
            | 0 -> DaylightType.Morning
            | 1 -> DaylightType.Noon
            | 2 -> DaylightType.Evening
            | _ -> DaylightType.Night

type Luminary () = 
    let isShine = 
        match gen.Next 2 with
        | 0 -> LuminaryType.NotShining
        | _ -> LuminaryType.Shining
    interface ILuminary with
        member this.IsShining() = 
            isShine = LuminaryType.Shining

type Wind () = 
    interface IWind with
        member this.Current = 
            match gen.Next 4 with
            | 0 -> WindType.NoWind
            | 1 -> WindType.WeakWind
            | 2 -> WindType.Breathe
            | _ -> WindType.Hurricane

type TrueWeather = 
    interface IWeatherFactory with
        member this.createDaylight() = new Daylight() :> IDayLight
        member this.createLuminary() = new Luminary() :> ILuminary
        member this.createWind() = new Wind() :> IWind

type Cloud (factory: IWeatherFactory) =
    let daylight = factory.createDaylight ()
    let luminary = factory.createLuminary ()
    let wind = factory.createWind ()
    member x.InternalCreate() =
        if daylight.Current = DaylightType.Night then
            if luminary.IsShining() then
                new Creature(CreatureType.Bat)
      // TODO – implement all other creatures
            else
                raise <| new System.NotImplementedException()
        else
            raise <| new System.NotImplementedException()
 
    member x.Create() =
      let creature = x.InternalCreate()
      let magic = new Magic()     
      magic.CallDaemon(creature.CreatureType)
      creature
