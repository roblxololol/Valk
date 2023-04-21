local StarterGui = game:GetService("StarterGui")
local Players = game:GetService("Players")
local LocalPlayer = Players.LocalPlayer
local Client = LocalPlayer
local Character = LocalPlayer.Character or LocalPlayer.CharacterAdded:Wait()
local GetPlayers = Players.GetPlayers
local Mouse = LocalPlayer:GetMouse()
local RunService = game:GetService("RunService")
local Camera = game.Workspace.CurrentCamera
local Players = game:GetService("Players")
local LocalPlayer = Players.LocalPlayer
local TPservice= game:GetService("TeleportService")
local GetPlayers = Players.GetPlayers
local Mouse = LocalPlayer:GetMouse()
local Workspace = game:GetService("Workspace")
local GuiService = game:GetService("GuiService")
local CurrentCamera = Workspace.CurrentCamera
local TeleportService = game:GetService("TeleportService")
local GetGuiInset = GuiService.GetGuiInset
local Circle1 = Drawing.new("Circle")
local Circle2 = Drawing.new("Circle")
local Plr,Plr2,IsTargetting

function WallCheck (destination, ignore)
    if (getgenv().Valk["Checks"].Wall) then
        local Origin = Camera.CFrame.p
        local CheckRay = Ray.new(Origin, destination - Origin)
        local Hit = game:GetService("Workspace"):FindPartOnRayWithIgnoreList(CheckRay, ignore)
        return Hit == nil
    else
        return true
    end
end

local WTS = (function(Object)
	local ObjectVector = CurrentCamera:WorldToScreenPoint(Object.Position)
	return Vector2.new(ObjectVector.X, ObjectVector.Y)
end)

local Filter = (function(obj)
	if (obj:IsA('BasePart')) then
		return true
	end
end)

local MousePosVector2 = (function()
	return Vector2.new(Mouse.X, Mouse.Y) 
end)

if getgenv().Valk["Options"].Loader and getgenv().Valk["Options"].LoaderType == "Notifications" then
wait(0.3)
    StarterGui:SetCore("SendNotification",{
        Title = "Valk.cc",
        Text = "Loaded"
    })
wait(0.5)
elseif getgenv().Valk["Options"].Loader and getgenv().Valk["Options"].LoaderType == "Image" then
wait(0.3)
        --
wait(0.5)
end

function AimbotFOV()
    if not (Circle1) then
        return
    end
    Circle1.Visible = getgenv().Valk["Fov"]["Aimbot"].Visible
    Circle1.Radius =  getgenv().Valk["Fov"]["Aimbot"].Size * 2.1
    Circle1.Position = Vector2.new(Mouse.X, Mouse.Y + GetGuiInset(GuiService).Y)
    Circle1.Filled = getgenv().Valk["Fov"]["Aimbot"].Filled
    Circle1.Transparency = getgenv().Valk["Fov"]["Aimbot"].Transparency
    Circle1.Thickness = getgenv().Valk["Fov"]["Aimbot"].Thickness
    Circle1.NumSides = getgenv().Valk["Fov"]["Aimbot"].Sides
    Circle1.Color = getgenv().Valk["Fov"]["Aimbot"].Color
    return Circle1
end

function SilentFOV()
  if not (Circle2) then
      return
  end
  Circle2.Visible = getgenv().Valk["Fov"]["Silent"].Visible
  Circle2.Radius =  getgenv().Valk["Fov"]["Silent"].Size * 2.1
  Circle2.Position = Vector2.new(Mouse.X, Mouse.Y + GetGuiInset(GuiService).Y)
  Circle2.Filled = getgenv().Valk["Fov"]["Silent"].Filled
  Circle2.Transparency = getgenv().Valk["Fov"]["Silent"].Transparency
  Circle2.Thickness = getgenv().Valk["Fov"]["Silent"].Thickness
  Circle2.NumSides = getgenv().Valk["Fov"]["Silent"].Sides
  Circle2.Color = getgenv().Valk["Fov"]["Silent"].Color
  return Circle2
end
RunService.Heartbeat:Connect(function() AimbotFOV() SilentFOV()end)


if getgenv().Valk["Fov"]["Aimbot"].UseFov == true then
    function NearestPerson()
        local closestPlayer
        local shortestDistance = getgenv().Valk["Fov"]["Aimbot"].Size
        for i, v in ipairs(game.Players:GetPlayers()) do
            pcall(function()
                if v ~= game.Players.LocalPlayer and v.Character and
                    v.Character:FindFirstChild("Humanoid") and WallCheck(v.Character.HumanoidRootPart.Position, {Client, v.Character})  then
                    local pos = CurrentCamera:WorldToViewportPoint(v.Character.PrimaryPart.Position)
                    local magnitude =
                    (Vector2.new(pos.X, pos.Y) - Vector2.new(Mouse.X, Mouse.Y)).magnitude
                    if (Vector2.new(pos.X, pos.Y) - Vector2.new(Mouse.X, Mouse.Y)).magnitude < shortestDistance then
                        closestPlayer = v
                        shortestDistance = magnitude
                    end
                end
            end)
        end
    return closestPlayer
  end
    elseif getgenv().Valk["Fov"]["Aimbot"].UseFov == false then
        function NearestPerson()
            local closestPlayer
            local shortestDistance = getgenv().Valk["Aimbot"].Distance
            for i, v in ipairs(game.Players:GetPlayers()) do
                pcall(function()
                    if v ~= game.Players.LocalPlayer and v.Character and
                        v.Character:FindFirstChild("Humanoid") and WallCheck(v.Character.HumanoidRootPart.Position, {Client, v.Character}) then
                        local pos = CurrentCamera:WorldToViewportPoint(v.Character.PrimaryPart.Position)
                        local magnitude =
                        (Vector2.new(pos.X, pos.Y) - Vector2.new(Mouse.X, Mouse.Y)).magnitude
                        if (Vector2.new(pos.X, pos.Y) - Vector2.new(Mouse.X, Mouse.Y)).magnitude < shortestDistance then
                            closestPlayer = v
                            shortestDistance = magnitude
                        end
                    end
                end)
            end
        return closestPlayer
    end
end

local ClosestPlrFromMouse = function()
    local Target = nil
    Closest = 1 / 0
    for _ ,v in ipairs(Players:GetPlayers()) do
        if (v.Character and v ~= Client and v.Character:FindFirstChild("HumanoidRootPart")) and WallCheck(v.Character.HumanoidRootPart.Position, {Client, v.Character})  then
            local Position, OnScreen = Camera:WorldToScreenPoint(v.Character.HumanoidRootPart.Position)
            local Distance = (Vector2.new(Position.X, Position.Y) - Vector2.new(Mouse.X, Mouse.Y)).Magnitude
            if (Circle2.Radius > Distance and Distance < Closest and OnScreen and Position) then
                Closest = Distance
                Target = v
            end
        end
    end
    return Target
end

local GetClosestBodyPart = (function()
	local ShortestDistance = math.huge
	local BodyPart = nil
	for _, v in next, game.Players:GetPlayers() do
		if (v ~= Client and v.Character and v.Character:FindFirstChild("Humanoid")) then
			for k, x in next, v.Character:GetChildren() do
				if (Filter(x)) then
					local Distance = (WTS(x) - MousePosVector2()).magnitude
					if (Distance < ShortestDistance) then
						ShortestDistance = Distance
						BodyPart = x
					end
				end
			end
		end
	end
	return BodyPart
end)

task.spawn(function ()
    while task.wait() do
            if Plr then
                if getgenv().Valk["Aimbot"].Enabled == true and getgenv().Valk["Aimbot"].HitboxAimType == "Closest" then
                    getgenv().Valk["Aimbot"].Hitbox = tostring(GetClosestBodyPart(Plr.Character))
                elseif getgenv().Valk["Aimbot"].Enabled == true and getgenv().Valk["Aimbot"].HitboxAimType == "Default" then
                    getgenv().Valk["Aimbot"].Hitbox = getgenv().Valk["Aimbot"].Hitbox
                elseif getgenv().Valk["Aimbot"].Enabled == true and getgenv().Valk["Aimbot"].HitboxAimType == "Point" then
                    getgenv().Valk["Aimbot"].Hitbox = tostring(ClosestPoint(Plr.Character))
                end
                if Plr2 then
                    if getgenv().Valk["Silent"].Enabled == true and getgenv().Valk["Silent"].HitboxAimType == "Closest" then
                        getgenv().Valk["Silent"].Hitboxes = tostring(GetClosestBodyPart(Plr.Character))
                    elseif getgenv().Valk["Silent"].Enabled == true and getgenv().Valk["Silent"].HitboxAimType == "Default" then
                        getgenv().Valk["Silent"].Hitboxes = getgenv().Valk["Silent"].Hitboxes
                    elseif getgenv().Valk["Silent"].Enabled == true and getgenv().Valk["Silent"].HitboxAimType == "Point" then
                        getgenv().Valk["Silent"].Hitboxes = tostring(ClosestPoint(Plr.Character))
                    end
               end
           end
      end
end)

if getgenv().Valk["Aimbot"].HitAirshots == true then
    if Plr.Character.Humanoid.Jump == true and Plr.Character.Humanoid.FloorMaterial == Enum.Material.Air then
        getgenv().Valk["Aimbot"].Hitbox = getgenv().Valk["Aimbot"].HitAirshotsHitbox
    else
        Plr.Character:WaitForChild("Humanoid").StateChanged:Connect(function(old,new)
            if new == Enum.HumanoidStateType.Freefall then
                getgenv().Valk["Aimbot"].Hitbox = getgenv()Valk["Aimbot"].HitAirshotsHitbox
            else
                getgenv().Valk["Aimbot"].Hitbox = getgenv().Valk["Aimbot"].Hitbox
            end
        end)
    end
end

Mouse.KeyDown:Connect(function(Key)
    local Keybind = getgenv().Valk["Aimbot"].AimbotKeybind:lower()
    if (Key == Keybind) then
        if getgenv().Valk["Aimbot"].Enabled == true then
            IsTargetting = not IsTargetting
            if IsTargetting then
            Plr = NearestPerson()
            else
                if Plr ~= nil then
                    Plr = nil
                end
            end
       end
    end
end)

RunService.RenderStepped:Connect(function()
    if getgenv().Valk["Aimbot"].Enabled == true and Plr and Plr.Character ~= nil then
        if getgenv().Valk["Aimbot"].Shaking then
            local Main = CFrame.new(Camera.CFrame.p,Plr.Character[getgenv().Valk["Aimbot"].Hitbox].Position + Plr.Character[getgenv().Valk["Aimbot"].Hitbox].Velocity*getgenv().Valk["Aimbot"].Prediction +
            Vector3.new(
                math.random(-getgenv().Valk["Aimbot"].SX,getgenv().Valk["Aimbot"].SX),
                math.random(-getgenv().Valk["Aimbot"].SY,getgenv().Valk["Aimbot"].SZ),
                math.random(-getgenv().Valk["Aimbot"].SZ,getgenv().Valk["Aimbot"].SZ)
            )*1)
            Camera.CFrame = Camera.CFrame:Lerp(Main,getgenv().Valk["Aimbot"].Smoothness,Enum.EasingStyle.Sine,Enum.EasingDirection.InOut,Enum.EasingStyle.Bounce,Enum.EasingDirection.Out,Enum.EasingStyle.Exponential,Enum.EasingDirection.Out)
        else
            local Main = CFrame.new(Camera.CFrame.p,Plr.Character[getgenv().Valk["Aimbot"].Hitbox].Position + Plr.Character[getgenv().Valk["Aimbot"].Hitbox].Velocity*getgenv().Valk["Aimbot"].Prediction)
            Camera.CFrame = Camera.CFrame:Lerp(Main,getgenv().Valk["Aimbot"].Smoothness,Enum.EasingStyle[getgenv().Valk["Aimbot"]["Easing"].Style],Enum.EasingDirection[getgenv().Valk["Aimbot"]["Easing"].Direction])
        end
    end
end)

RunService.Heartbeat:Connect(function()
                if getgenv().Valk["Aimbot"].Enabled == true and Plr and Plr.Character ~= nil then
        if getgenv().Valk["Checks"].Knock then
            if Plr.Character.BodyEffects["K.O"].Value then Plr = nil 
            end
        end
        end
end)

RunService.Heartbeat:Connect(function()
    if getgenv().Valk["Fov"]["Dynamic"].Enabled and getgenv().Valk["Fov"]["Dynamic"].Circle == "Silent" and Client ~= nil and
        (Client.Character) and Plr2 and Plr2.Character then
        if (Client.Character.HumanoidRootPart.Position - Plr2.Character.HumanoidRootPart.Position).Magnitude <
        getgenv().Valk["Fov"]["Dynamic"].Close_Studs then
            getgenv().Valk["Fov"]["Silent"].Size = getgenv().Valk["Fov"]["Dynamic"].Close
        elseif (Client.Character.HumanoidRootPart.Position - Plr2.Character.HumanoidRootPart.Position).Magnitude <
        getgenv().Valk["Fov"]["Dynamic"].Mid_Studs then
            getgenv().Valk["Fov"]["Silent"].Size = getgenv().Valk["Fov"]["Dynamic"].Mid
        elseif (Client.Character.HumanoidRootPart.Position - Plr2.Character.HumanoidRootPart.Position).Magnitude <
        getgenv().Valk["Fov"]["Dynamic"].Far_Studs then
            getgenv().Valk["Fov"]["Silent"].Size = getgenv().Valk["Fov"]["Dynamic"].Far
        elseif (Client.Character.HumanoidRootPart.Position - Plr2.Character.HumanoidRootPart.Position).Magnitude <
        getgenv().Valk["Fov"]["Dynamic"].VeryFar_Studs then
            getgenv().Valk["Fov"]["Silent"].Size = getgenv().Valk["Fov"]["Dynamic"].VeryFar
        end
    end
end)

RunService.RenderStepped:Connect(function()
    if getgenv().Valk["Aimbot"].Smoothing and getgenv().Valk["Aimbot"].Enabled  == true then
        local Main = CFrame.new(workspace.CurrentCamera.CFrame.p, Plr.Character[getgenv().Valk["Aimbot"].Hitbox].Position + Plr.Character[getgenv().Valk["Aimbot"].Hitbox].Velocity*getgenv().Valk["Aimbot"].Prediction)
                                     workspace.CurrentCamera.CFrame = workspace.CurrentCamera.CFrame:Lerp(Main,getgenv().Valk["Aimbot"].Smoothness,Enum.EasingStyle[getgenv().Valk["Aimbot"]["Easing"].Style],Enum.EasingDirection[getgenv().Valk["Aimbot"]["Easing"].Direction])
    elseif getgenv().Valk["Aimbot"].Smoothing == false and  getgenv().Valk["Aimbot"].Enabled == true then
        workspace.CurrentCamera.CFrame = CFrame.new(workspace.CurrentCamera.CFrame.Position, Plr.Character[getgenv().Valk["Aimbot"].Hitbox].Position + Plr.Character[getgenv().Valk["Aimbot"].Hitbox].Velocity*getgenv().Valk["Aimbot"].Prediction)
                                end
end)

local grmt = getrawmetatable(game)
local backupindex = grmt.__index
setreadonly(grmt, false)

grmt.__index = newcclosure(function(self, v)
if (getgenv().Valk["Silent"].Enabled and Mouse and tostring(v) == "Hit") then
    Plr2 = ClosestPlrFromMouse()
    if Plr2 then
        local endpoint = game.Players[tostring(Plr2)].Character[getgenv().Valk["Silent"]["Hitboxes"]].CFrame + (
            game.Players[tostring(Plr2)].Character[getgenv().Valk["Silent"]["Hitboxes"]].Velocity *getgenv().Valk["Silent"].Prediction
        )
        return (tostring(v) == "Hit" and endpoint)
    end
end
return backupindex(self, v)
end)

RunService.RenderStepped:Connect(function()
    if getgenv().Valk["TriggerBot"].Enabled then
        if Mouse.Target then
            if Mouse.Target.Parent:FindFirstChild('Humanoid') and Mouse.Target.Parent:FindFirstChild('Head') and Mouse.Target.Parent:FindFirstChild('LowerTorso') and Mouse.Target.Parent:FindFirstChild('UpperTorso') then
                if getgenv().Valk["TriggerBot"].Delay then
                    wait(getgenv().Valk["TriggerBot"].Delayness)
                    mouse1click()
                    mouse1release()
                else
                    mouse1click()
                    mouse1release()
                end
            end
        end
    end
end)

Mouse.KeyDown:Connect(
  function(Key)
    if getgenv().Valk["TriggerBot"].EnabledTriggerKey then
    if (Key ==  getgenv().Valk["TriggerBot"].TriggerKeybind:lower()) then
        if  getgenv().Valk["TriggerBot"].Enabled == true then
            getgenv().Valk["TriggerBot"].Enabled = false
            StarterGui:SetCore("SendNotification",{
                Title = "Valk.cc",
                Text = "TB Disabled"
            })
        else
            getgenv().Valk["TriggerBot"].Enabled = true
            StarterGui:SetCore("SendNotification",{
                Title = "Valk.cc",
                Text = "TB Enabled"
            })
        end
    end
  end
end
)

task.spawn(function()
    if getgenv().Valk["Checks"].NoGroundShots and Plr2.Character[getgenv().Valk["Silent"].Hitboxes].Velocity.Y < -15 then
        pcall(function()
            local Target = Plr2.Character[getgenv().Valk["Silent"].Hitboxes]
            Target.Velocity = Vector3.new(Target.Velocity.X, (Target.Velocity.Y / 5), Target.Velocity.Z)
            Target.AssemblyLinearVelocity = Vector3.new(Target.Velocity.X, (Target.Velocity.Y / 5), Target.Velocity.Z)
        end)
    end
end)

Client.Chatted:Connect(function(message)
    if getgenv().Valk["Chat"].Enabled then
        local args = string.split(message, " ")
        if args[1] == getgenv().Valk["Chat"].CircleSize and getgenv().Valk["Chat"].Circle == "Silent" and args[2] ~= nil then
            getgenv().Valk["Fov"]["Silent"].Size = tonumber(args[2])
        elseif args[1] == getgenv().Valk["Chat"].CircleSize and getgenv().Valk["Chat"].Circle == "Aimbot" and args[2] ~= nil then
            getgenv().Valk["Fov"]["Aimbot"].Size = tonumber(args[2])
        end
    end
    if getgenv().Valk["Chat"].Enabled then
        local args = string.split(message, " ")
        if args[1] == getgenv().Valk["Chat"].PredictionAmount and getgenv().Valk["Chat"].Prediction == "Silent" and args[2] ~= nil then
            getgenv().Valk["Silent"].Prediction = tonumber(args[2])
        elseif args[1] == getgenv().Valk["Chat"].PredictionAmount and getgenv().Valk["Chat"].Prediction == "Aimbot" and args[2] ~= nil then
            getgenv().Valk["Aimbot"].Prediction = tonumber(args[2])
        end
    end
end)

Mouse.KeyDown:Connect(
  function(Key)
    if getgenv().Valk["Silent"].EnabledSilentKeybind then
    if (Key ==  getgenv().Valk["Silent"].SilentKeybind:lower()) then
        if getgenv().Valk["Silent"].Enabled == true then
            getgenv().Valk["Silent"].Enabled = false
            StarterGui:SetCore("SendNotification",{
                Title = "Valk.cc",
                Text = "SA Disabled"
            })
        else
            getgenv().Valk["Silent"].Enabled = true
            StarterGui:SetCore("SendNotification",{
                Title = "Valk.cc",
                Text = "SA Enabled"
            })
        end
    end
  end
end
)

if (targ.Character.HumanoidRootPart.Velocity.Y < -5 and targ.Character.Humanoid:GetState() ~= Enum.HumanoidStateType.Freefall) or targ.Character.HumanoidRootPart.Velocity.Y < -50 then
        return true
    elseif targ and (targ.Character.HumanoidRootPart.Velocity.X > 35 or targ.Character.HumanoidRootPart.Velocity.X < -35) then
        return true
    elseif targ and targ.Character.HumanoidRootPart.Velocity.Y > 60 then
        return true
    elseif targ and (targ.Character.HumanoidRootPart.Velocity.Z > 35 or targ.Character.HumanoidRootPart.Velocity.Z < -35) then
        return true
    else
        return false
end

oroutine.resume(coroutine.create(function()
    while true do
        if AutoPrediction.Enabled then
            local ping = game:GetService("Stats").Network.ServerStatsItem["Data Ping"]:GetValue()
            if ping <= 40 then
                Silent.Prediction = AutoPrediction.ping30_40
            elseif ping <= 50 then
               Silent.Prediction = AutoPrediction.ping40_50
            elseif ping <= 60 then
                Silent.Prediction = AutoPrediction.ping50_60
            elseif ping <= 70 then
               Silent.Prediction = AutoPrediction.ping60_70
            elseif ping <= 80 then
               Silent.Prediction = AutoPrediction.ping70_80
            elseif ping <= 90 then
                Silent.Prediction = AutoPrediction.ping80_90
            elseif ping <= 100 then
               Silent.Prediction = AutoPrediction.ping90_100
            elseif ping <= 110 then
                Silent.Prediction = AutoPrediction.ping100_110
            elseif ping <= 120 then
               Silent.Prediction = AutoPrediction.ping110_120
            elseif ping <= 130 then
                Silent.Prediction = AutoPrediction.ping120_130
            elseif ping <= 140 then
               Silent.Prediction = AutoPrediction.ping130_140
            elseif ping <= 150 then
               Silent.Prediction = AutoPrediction.ping140_150
            elseif ping <= 160 then
                Silent.Prediction = AutoPrediction.ping150_160
            elseif ping <= 170 then
                Silent.Prediction = AutoPrediction.ping160_170
            elseif ping <= 180 then
                Silent.Prediction = AutoPrediction.ping170_180
            elseif ping <= 190 then
                Silent.Prediction = AutoPrediction.ping180_190
            elseif ping <= 200 then
                Silent.Prediction = AutoPrediction.ping190_200
            end
            task.wait(0.7)
        end
    end
end))
