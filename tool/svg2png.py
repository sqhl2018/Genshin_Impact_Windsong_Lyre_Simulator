import cairosvg

def s_to_p(fromFile,toFile,scale):
    fileHandle = open(fromFile)
    svg = fileHandle.read()
    fileHandle.close()
    cairosvg.svg2png(bytestring=svg, write_to=toFile,scale=scale,dpi=360)


targetDir="../res/"

clefScale=4.0 
noteScale=1.0

# clefScale=3.2 
# noteScale=0.8

# clefScale=3.6
# noteScale=0.9

s_to_p("./svgs/clef.svg",targetDir+"clef.png",clefScale)
s_to_p("./svgs/clef_base.svg",targetDir+"clef_base.png",clefScale)
s_to_p("./svgs/clef_tensor.svg",targetDir+"clef_tensor.png",clefScale)



s_to_p("./svgs/do.svg",targetDir+"do.png",noteScale)
s_to_p("./svgs/re.svg",targetDir+"re.png",noteScale)
s_to_p("./svgs/mi.svg",targetDir+"mi.png",noteScale)
s_to_p("./svgs/fa.svg",targetDir+"fa.png",noteScale)
s_to_p("./svgs/so.svg",targetDir+"so.png",noteScale)
s_to_p("./svgs/la.svg",targetDir+"la.png",noteScale)
s_to_p("./svgs/ti.svg",targetDir+"ti.png",noteScale)

s_to_p("./svgs/do_down.svg",targetDir+"do_down.png",noteScale)
s_to_p("./svgs/re_down.svg",targetDir+"re_down.png",noteScale)
s_to_p("./svgs/mi_down.svg",targetDir+"mi_down.png",noteScale)
s_to_p("./svgs/fa_down.svg",targetDir+"fa_down.png",noteScale)
s_to_p("./svgs/so_down.svg",targetDir+"so_down.png",noteScale)
s_to_p("./svgs/la_down.svg",targetDir+"la_down.png",noteScale)
s_to_p("./svgs/ti_down.svg",targetDir+"ti_down.png",noteScale)

s_to_p("./svgs/donghua.svg",targetDir+"donghua.png",noteScale)


# s_to_p("./svgs/close.svg",targetDir+"close.png",noteScale)
# s_to_p("./svgs/min.svg",targetDir+"min.png",noteScale)