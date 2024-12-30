function game.initialize()
    print("Hello World from Lua!")
    font = gameEngine.Font.new("Arial", false, false, true, 30)
    --print(gameEngine.Font)
    print("Hello font from Lua!")
end

-- look for global table "game"
-- get field "initialize"
-- push arguments
-- call function
-- game.initialize()

function game.paint(rect)
    --print("paint("..rect.left..", "..rect.top..", "..rect.right..", "..rect.bottom..")")
    gameEngine.setColor(0x0000FF)
    gameEngine.setFont(font)
    gameEngine.drawString("Hello World with a font!", 200, 200)
    gameEngine.fillRect(20, 20, 100, 100)
end

function game.mouseButtonAction(isLeft, isDown, x, y)
    if not isLeft then
        gameEngine.quit()
    end
end

function game.mouseWheelAction(x, y, distance)
    print("scroll(Xpos: "..x..", Ypos: "..y..", distance: "..distance..")")
end