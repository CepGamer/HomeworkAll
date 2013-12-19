module ui
open System.Windows.Forms
open System.Drawing
open System.IO
open System.Text
open System

type World = Water | Terrain | Mountain

type MButton() as this = 
    member x.create name =
        let mutable lc = 
            match name with
            | "Water" -> 1
            | "Terrain" -> 2
            | "Mountain" -> 3
            | "Import" -> 4
            | _ -> failwith "Wrong button name"
        new Button( Text = name,
                    Height = 70,
                    Width = 70,
                    Visible = true,
                    Enabled = true,
                    Left = 520,
                    Top = 10 * lc + 70 * (lc - 1))

type MForm() as this = 
    inherit Form(Width = 610, Height = 550, MaximizeBox = false, FormBorderStyle = FormBorderStyle.Fixed3D)
    let blue = new SolidBrush(Color.Blue)
    let green = new SolidBrush(Color.Green)
    let brown = new SolidBrush(Color.Brown)
    let creator = new MButton()

    let filePath = sprintf "%s\\import.txt" <| Environment.GetFolderPath Environment.SpecialFolder.MyDocuments
    let sw = new StreamWriter (filePath)
    
    let horBord = 500 / 50
    let verBord = 500 / 50
    let mutable penType = Water
    let mutable map = Array2D.init 50 50 (fun _ _ -> Water)
        
    let buttonW = creator.create "Water"
    let buttonT = creator.create "Terrain"
    let buttonM = creator.create "Mountain"
    let buttonS = creator.create "Import"


    let easel = new PictureBox( Height = 500,
                                Width = 500,
                                Top = 10,
                                Left = 10,
                                Visible = true,
                                Enabled = true)

    let easPaint (e: PaintEventArgs) = 
        e.Graphics.Clear(Color.White)
        for i in 0..49 do
            for j in 0..49 do
                let br = 
                    match map.[i, j] with
                    | Water -> blue
                    | Terrain -> green
                    | Mountain -> brown
                e.Graphics.FillRectangle (br, horBord * i, verBord * j, horBord, verBord)

    let easMD (e: MouseEventArgs) = 
        let a = e.Location
        map.[a.X / 10, a.Y / 10] <- penType
        easel.Refresh ()

    let easMM (e: MouseEventArgs) = 
        let a = e.Location
        if e.Button <> MouseButtons.None then 
            if a.X < 500 && a.X >= 0 && a.Y < 500 && a.Y >= 0 then
                if map.[a.X / 10, a.Y / 10] <> penType then 
                    map.[a.X / 10, a.Y / 10] <- penType
                    easel.Refresh()
    
    let import(arg: EventArgs) =         
        let a = Array2D.map ( fun x -> match x with
                                       | Water -> 'w'
                                       | Mountain -> 'm'
                                       | Terrain -> 't') map
        let mutable x = ""
        for i in 0..49 do
            for j in 0..49 do
                x <- sprintf "%s%s" x (a.[j, i].ToString())
            x <- sprintf "%s\n" x
        sw.Write x
        sw.Flush()

    do
        this.Controls.Add buttonW
        this.Controls.Add buttonT
        this.Controls.Add buttonM
        this.Controls.Add buttonS
        this.Controls.Add easel
        buttonW.Click.Add (fun _ -> penType <- Water)
        buttonT.Click.Add (fun _ -> penType <- Terrain)
        buttonM.Click.Add (fun _ -> penType <- Mountain)
        buttonS.Click.Add import
        easel.Paint.Add easPaint
        easel.MouseDown.Add easMD
        easel.MouseMove.Add easMM

[<EntryPoint>]
Application.Run(new MForm())
