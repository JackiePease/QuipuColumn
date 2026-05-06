# QuipuColumn

This was a project I did for [Civic Data Cooperative's Fesival of Data](https://civicdatacooperative.com/festival-of-data/) in Liverpool, an interactive 3-day event, which took place on 5,6,7 February 2026.

With children from Lawrence Primary School, and volunteers from Liverpool University, I made a ![Quipu Column] with knotted cords and LED strips hanging down from a central column made from a clear HIPS pipe and an Armadillo bike lane separator. 

The LED strips were fed through the pipe to a disk at the bottom and controlled by 3 [MCQN Ltd My Bikes Got LED boards](https://github.com/mcqn/my-bikes-got-led).

The column was a bit unstable at the event, so I bought a large parasol stand to replace the Armadillo. Unfortunately although this said it took a 50mm pole, it's actually designed for an American measurement (equivalent to 48.3mm). I resized the 3D print designs to fit, and also made some changes to the design (e.g. not having the LEDs starting from higher than the cords, cutting larger parts on the laser cutter as the big 3D printer at DoES Liverpool was out of action, and having the LEDs going up the outside of the pipe).

In the end I didn't use the LEDs when showing this at Wirral MakeFest, but the option is still there.

## Files in this Repository
### 3D Printing and Laser Cutting Files (all designed in OnShape)

![Small 3D printed Maquette](/3D_printing_and_laser_cutting_files/6_boroughs.stl)

#### For 50mm pipe

![Corner Part](/3D_printing_and_laser_cutting_files/for_50mm_pipe/corner_part.dxf) - corner for laser cut hexagon edge shape DXF
![Hold Bar](/3D_printing_and_laser_cutting_files/for_50mm_pipe/hold_bar.stl) - unused 3D printed side part for ropes to go attach to at the base (difficult to print)
![New Top Part](/3D_printing_and_laser_cutting_files/for_50mm_pipe/new_top.stl)(part that fits over the top of the pipe)
![New Wheel](/3D_printing_and_laser_cutting_files/for_50mm_pipe/new_wheel.stl) - larger diameter 3D printed part that attaches to new top part
![Side part](/3D_printing_and_laser_cutting_files/for_50mm_pipe/side_part.dxf) - Hexagon edge parts
![](/3D_printing_and_laser_cutting_files/for_50mm_pipe/wheel.stl)

#### For 48.3mm pipe

![Base Clip](/3D_printing_and_laser_cutting_files/for_50mm_pipe/base_clip.stl) - Attached to base - ropes feed through and are attached underneath
![](/3D_printing_and_laser_cutting_files/for_50mm_pipe/base_clip_LEDs.stl) - 
Base clips for LEDs (not currently used)
![Corner support](/3D_printing_and_laser_cutting_files/for_50mm_pipe/corner_support.stl) - 2 of these are used to attach to previously unsupported corners of the large hexagon (in this version its screwed on to the parasol stand in 2 places)
![MDF electric wheel](/3D_printing_and_laser_cutting_files/for_50mm_pipe/mdf_electric_wheel.dxf) - allows MCQN My Bike's Got LED boards to be attached at the base with wires or unlit LED strips going up through the pipe
![Plugs](/3D_printing_and_laser_cutting_files/for_50mm_pipe/plug.stl) - Go through holes in the top part to allow cords to be attached with key rings
![Separator](/3D_printing_and_laser_cutting_files/for_50mm_pipe/separator.stl) - Attaches to the cord to separate 10s and units etc.
![10mm separator](/3D_printing_and_laser_cutting_files/for_50mm_pipe/separator_10mm.stl)
![12mm separator](/3D_printing_and_laser_cutting_files/for_50mm_pipe/separator_12mm.stl)
![Top part](/3D_printing_and_laser_cutting_files/for_50mm_pipe/top_part.stl)
![Top part without side holes](/3D_printing_and_laser_cutting_files/for_50mm_pipe/top_part_no_side_holes.stl)
![Wheel part for top](/3D_printing_and_laser_cutting_files/for_50mm_pipe/wheel.stl)

### Photos

![Small 3D printed Maquette](/photos/maquette.png)

#### Original Quipu Column at the Festival

![Close up of knotted cords/ropes](/photos/Original_Quipu_Column_For_Festival/Close_Up_Of_Knotted_Cords_And_LEDs.png)
![Quipu in the main room at the Festival](/photos/Original_Quipu_Column_For_Festival/Quipu_at_festival.png)
![Base of the column](/photos/Original_Quipu_Column_For_Festival/Column_Base.png)

#### Quipu Column as rebuilt for Wirral MakeFest

![Base of Quipu Column](/photos/Quipu_Column_Rebuilt_For_Wirral_MakeFest/Base_of_Quipu_Column.png)
![Quipu Column at DoES Liverpool](/photos/Quipu_Column_Rebuilt_For_Wirral_MakeFest/Quipu_Column_At_DoES_Liverpool.png)
![Close up of knotted cords](/photos/Quipu_Column_Rebuilt_For_Wirral_MakeFest/Knotted_Cords.png)
![Top of column showing cord attachment](/photos/Quipu_Column_Rebuilt_For_Wirral_MakeFest/Top_of_Quipu_Column.png)

### Code

![Arduino code for the LEDs on the original column](/code/base_sketch.ino)
It was difficult to code WLED to show different numbers of lit up LEDs in different segments, and I didn't need the Wifi part, so I ended up using the boards as Arduinos. It may be simpler with the new version of WLED - to be checked. I originally had the LEDs moving, but they needed to be static for readability. 
As the room was quite dark, the cords were hard to read when the LEDs were on full brightness - the brightness had to be reduced a lot to allow both to be read.

### Documents

![Example numbers converted to Quipu cords](/documents/examples.odt)
![Key for Knots and LEDs](/knotkey.odt/)
