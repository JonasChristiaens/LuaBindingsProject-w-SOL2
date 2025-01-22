-- =================
--      GLOBALS
-- =================
-- booleans needed to check game states
g_StartGame = false
g_FirstClick = true
g_GameWon = false
g_GameLost = false

-- "struct" & "enum" used for the minesweeper field
g_Cells = {}
g_Cellstates = {
    hidden = 1,
    revealed = 2,
    flagged = 3,
    bomb = 4
}
g_GridPos = {
    x = 180,
    y = 145
}

-- game & field variables
g_AmmountOfBombs = 0
g_CellSize = 0
g_Rows = 25
g_Columns = 25


-- ===================
--      FUNCTIONS
-- ===================
function game.start()
    -- =================
    -- load all Textures
    -- =================

    -- screen textures
    introScreenTexture = gameEngine.Bitmap.new("./resources/Introscreen.png", true)
    loseScreenTexture = gameEngine.Bitmap.new("./resources/Losescreen.png", true)
    winScreenTexture = gameEngine.Bitmap.new("./resources/Winscreen.png", true)

    -- game asset textures
    cellsTexture = gameEngine.Bitmap.new("./resources/CellsTexture.png", true)
    mineTexture = gameEngine.Bitmap.new("./resources/Mine.png", true)
    flagTexture = gameEngine.Bitmap.new("./resources/Flag.png", true)

    -- button textures
    difficultyButton = gameEngine.Bitmap.new("./resources/DifficultyButton.png", true)
    easyButton = gameEngine.Bitmap.new("./resources/EasyButton.png", true)
    mediumButton = gameEngine.Bitmap.new("./resources/MediumButton.png", true)
    hardButton = gameEngine.Bitmap.new("./resources/HardButton.png", true)
    restartButton = gameEngine.Bitmap.new("./resources/RestartButton.png", true)
end

function game.paint()
    -- draw Intro Screen
    gameEngine.drawBitmapScale(introScreenTexture, 0, 0, 0, 0, introScreenTexture:GetWidth(), introScreenTexture:GetHeight(), gameEngine.getWidth(), gameEngine.getHeight())
    if not g_StartGame then
        -- draw buttons
        gameEngine.drawButton(easyButton, (gameEngine.getWidth() / 3) - ((gameEngine.getWidth() / 3) / 2) - (easyButton:GetWidth() / 2), gameEngine.getHeight() / 2, 0, 0, easyButton:GetWidth(), easyButton:GetHeight() / 3)
        gameEngine.drawButton(mediumButton, ((gameEngine.getWidth() / 3) * 2) - ((gameEngine.getWidth() / 3) / 2) - (mediumButton:GetWidth() / 2), gameEngine.getHeight() / 2, 0, 0, mediumButton:GetWidth(), mediumButton:GetHeight() / 3)
        gameEngine.drawButton(hardButton, ((gameEngine.getWidth() / 3) * 3) - ((gameEngine.getWidth() / 3) / 2) - (hardButton:GetWidth() / 2), gameEngine.getHeight() / 2, 0, 0, hardButton:GetWidth(), hardButton:GetHeight() / 3)
    
    else
        if g_GameLost then
            gameEngine.drawBitmapScale(loseScreenTexture, 0, 0, 0, 0, loseScreenTexture:GetWidth(), loseScreenTexture:GetHeight(), gameEngine.getWidth(), gameEngine.getHeight())
        end
        if g_GameWon then
            gameEngine.drawBitmapScale(winScreenTexture, 0, 0, 0, 0, winScreenTexture:GetWidth(), winScreenTexture:GetHeight(), gameEngine.getWidth(), gameEngine.getHeight())
        end
        
        DrawCells()

    end
end

function game.mouseButtonAction(isLeft, isDown, x, y)
    -- x & y is mouse position
    if not isDown and g_StartGame then
        local rowIdx = GetRowIndex(x, y, g_GridPos.x, g_GridPos.y, g_GridPos.x + (g_Columns * g_CellSize), g_GridPos.y + (g_Rows * g_CellSize))
        local colIdx = GetColumnIndex(x, y, g_GridPos.x, g_GridPos.y, g_GridPos.x + (g_Columns * g_CellSize), g_GridPos.y + (g_Rows * g_CellSize))

        local newRow = math.floor(rowIdx)
        local newCol = math.floor(colIdx) + 1


        if isLeft and not isDown then
            if g_FirstClick and newRow ~= -1 and newCol ~= -1 then
                g_FirstClick = false
                PlaceMines(newRow, newCol)
            
                CalculateAdjacentMines()
                LeftMouseButtonAction(newRow, newCol)

            elseif x ~= -1 and y ~= -1 then
                LeftMouseButtonAction(newRow, newCol)

            end
            
        elseif not isLeft and not isDown then
            RightMouseButtonAction(newRow, newCol)

        end
    end

    if not isDown and not g_StartGame then
        if gameEngine.isPointInRect(x, y, (gameEngine.getWidth() / 3) - ((gameEngine.getWidth() / 3) / 2) - (easyButton:GetWidth() / 2), gameEngine.getHeight() / 2, easyButton:GetWidth(), easyButton:GetHeight() / 3) then
            -- set current game state
            g_StartGame = true

            -- initialize cell array
            for i = 1, 25, 1 
            do
                g_Cells[i] = {state = 1, isBomb = false, adjacentMinesAmmount = 0}
            end
            
            -- set game variables
            g_AmmountOfBombs = 4
            g_CellSize = 130
            g_Rows = 5
            g_Columns = 5
        end
    
        if gameEngine.isPointInRect(x, y, ((gameEngine.getWidth() / 3) * 2) - ((gameEngine.getWidth() / 3) / 2) - (mediumButton:GetWidth() / 2), gameEngine.getHeight() / 2, easyButton:GetWidth(), easyButton:GetHeight() / 3) then
            -- set current game state
            g_StartGame = true

            -- initialize cell array
            for i = 1, 225, 1 
            do
                g_Cells[i] = {state = 1, isBomb = false, adjacentMinesAmmount = 0}
            end

            -- set game variables
            g_AmmountOfBombs = 35
            g_CellSize = 43
            g_Rows = 15
            g_Columns = 15
            
            
        end
    
        if gameEngine.isPointInRect(x, y, ((gameEngine.getWidth() / 3) * 3) - ((gameEngine.getWidth() / 3) / 2) - (hardButton:GetWidth() / 2), gameEngine.getHeight() / 2, easyButton:GetWidth(), easyButton:GetHeight() / 3) then
            -- set current game state
            g_StartGame = true

            -- initialize cell array
            for i = 1, 625, 1 
            do
                g_Cells[i] = {state = 1, isBomb = false, adjacentMinesAmmount = 0}
            end

            -- set game variables
            g_AmmountOfBombs = 125
            g_CellSize = 26
            g_Rows = 25
            g_Columns = 25

            
        end 
    end 
end

function DrawCells()
    for rowIndex = 0, g_Rows - 1 do
        for colIndex = 1, g_Columns do

            local x = g_GridPos.x + (colIndex - 1) * g_CellSize
            local y = g_GridPos.y + (rowIndex) * g_CellSize

            local left = math.floor(x)
            local top = math.floor(y)
            local width = math.floor(g_CellSize)
            local height = math.floor(g_CellSize)

            if g_Cells[rowIndex * g_Columns + colIndex].state == g_Cellstates.hidden then 
                gameEngine.drawBitmapScale(cellsTexture, left, top, 0, 0, cellsTexture:GetWidth() / 10, cellsTexture:GetHeight(), width, height)
            end
            if g_Cells[rowIndex * g_Columns + colIndex].state == g_Cellstates.revealed then
                gameEngine.drawBitmapScale(cellsTexture, left, top, (cellsTexture:GetWidth() / 10) * (g_Cells[rowIndex * g_Columns + colIndex].adjacentMinesAmmount + 1), 0, cellsTexture:GetWidth() / 10, cellsTexture:GetHeight(), width, height)
            end
            if g_Cells[rowIndex * g_Columns + colIndex].state == g_Cellstates.flagged then
                gameEngine.drawBitmapScale(flagTexture, left, top, 0, 0, flagTexture:GetWidth(), flagTexture:GetHeight(), width, height)
            end
            if g_Cells[rowIndex * g_Columns + colIndex].state == g_Cellstates.bomb then
                gameEngine.drawBitmapScale(mineTexture, left, top, 0, 0, mineTexture:GetWidth(), mineTexture:GetHeight(), width, height)
            end
        end
    end
end

function PlaceMines(rowIdx, colIdx)

    for minecount = 0, g_AmmountOfBombs - 1 do
        
        local row = 0
        local col = 0

        repeat
            row = math.floor(math.random(0, g_Rows - 1))
            col = math.floor(math.random(g_Columns))

        until( g_Cells[row * g_Columns + col].isBomb == false or row ~= rowIdx and col ~= colIdx )

        g_Cells[row * g_Columns + col].isBomb = true;
    end
end

function CalculateAdjacentMines()
    for rowCount = 0, g_Rows - 1 do
        for colCount = 1, g_Columns do
            if not g_Cells[rowCount * g_Columns + colCount].isBomb then
                g_Cells[rowCount * g_Columns + colCount].adjacentMinesAmmount = CountAdjacentMines(rowCount, colCount);
            end
        end
    end
end

function CountAdjacentMines(row, col)
    local count = 0
    for rowCount = -1, 1 do
        for colCount = -1, 1 do
            local newRow = row + rowCount
            local newCol = col + colCount

            if newCol > g_Columns or newRow >= g_Rows or newCol < 1 or newRow < 0 then 
                
            elseif g_Cells[newRow * g_Columns + newCol].isBomb == true then
                count = count + 1
            end 
        end
    end

    return count
end

function LeftMouseButtonAction(row, col)
    if row ~= -1 and col ~= -1 then
        if not g_Cells[row * g_Columns + col].isBomb then
            if g_Cells[row * g_Columns + col].state == g_Cellstates.hidden then
                if g_Cells[row * g_Columns + col].adjacentMinesAmmount == 0 then
                    RevealCellAndNeighbours(row, col)
                else
                    g_Cells[row * g_Columns + col].state = g_Cellstates.revealed   
                end
            end

            if g_Cells[row * g_Columns + col].state == g_Cellstates.flagged then
                if g_Cells[row * g_Columns + col].adjacentMinesAmmount == 0 then
                    RevealCellAndNeighbours(row, col)
                else
                    g_Cells[row * g_Columns + col].state = g_Cellstates.hidden   
                end
            end

            if CheckWin then
                WinGame()
            end
        else
            if g_Cells[row * g_Columns + col].state == g_Cellstates.hidden then
                g_Cells[row * g_Columns + col].state = g_Cellstates.bomb
                LoseGame()
            end

            if g_Cells[row * g_Columns + col].state == g_Cellstates.flagged then
                g_Cells[row * g_Columns + col].state = g_Cellstates.bomb
                LoseGame()
            end
        end
    end
end

function RevealCellAndNeighbours(row, col)
    if row < 0 or col < 1 or row >= g_Rows or col > g_Columns or g_Cells[row * g_Columns + col].state == g_Cellstates.revealed then
        return
    end

    g_Cells[row * g_Columns + col].state = g_Cellstates.revealed

    if g_Cells[row * g_Columns + col].adjacentMinesAmmount == 0 then
        for rowCheck = -1, 1 do
            for colCheck = -1, 1 do
                local newRow = row + rowCheck
                local newCol = col + colCheck

                RevealCellAndNeighbours(newRow, newCol)
            end
        end
    end
end

function RightMouseButtonAction(row, col)
    if row ~= -1 and col ~= -1 then
        if g_Cells[row * g_Columns + col].state == g_Cellstates.hidden then
            g_Cells[row * g_Columns + col].state = g_Cellstates.flagged
        
        elseif g_Cells[row * g_Columns + col].state == g_Cellstates.flagged then
            g_Cells[row * g_Columns + col].state = g_Cellstates.hidden
        end
    end
end

function CheckWin()
    for rowIdx = 0, g_Rows - 1 do
        for colIdx = 1, g_Columns do
            if not g_Cells[rowIdx * g_Columns + colIdx].isBomb and g_Cells[rowIdx * g_Columns + colIdx].state == g_Cellstates.hidden then
                return false
            end
            if not g_Cells[rowIdx * g_Columns + colIdx].isBomb and g_Cells[rowIdx * g_Columns + colIdx].state == g_Cellstates.flagged then
                return false
            end
        end
    end
end

function WinGame()
    g_GameWon = true

    for rowIdx = 0, g_Rows - 1 do
        for colIdx = 1, g_Columns do
            if g_Cells[rowIdx * g_Columns + colIdx].isBomb then
                g_Cells[rowIdx * g_Columns + colIdx].state = g_Cellstates.bomb
            end
        end
    end
end

function LoseGame()
    g_GameLost = true

    for rowIdx = 0, g_Rows - 1 do
        for colIdx = 1, g_Columns do
            if g_Cells[rowIdx * g_Columns + colIdx].isBomb then
                g_Cells[rowIdx * g_Columns + colIdx].state = g_Cellstates.bomb
            end
        end
    end
end

function GetColumnIndex(xPos, yPos, rectLeft, rectTop, rectRight, rectBottom)
    if not gameEngine.isPointInRect(xPos, yPos, rectLeft, rectTop, rectRight, rectBottom) then
        return -1
    end

    return (xPos - rectLeft) / g_CellSize
end

function GetRowIndex(xPos, yPos, rectLeft, rectTop, rectRight, rectBottom)
    if not gameEngine.isPointInRect(xPos, yPos, rectLeft, rectTop, rectRight, rectBottom) then
        return -1
    end

    return (yPos - rectTop) / g_CellSize
end

-- function IsPointInRect(xPos, yPos, rectLeft, rectTop, rectRight, rectBottom)
--     local inHorizontal = xPos >= rectangle.left and xPos < rectangle.left + (rectangle.right - rectangle.left)
--     local inVertical = yPos >= rectangle.top and yPos <= rectangle.top + (rectangle.bottom - rectangle.top)

--     return inHorizontal and inVertical
-- end