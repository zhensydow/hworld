dtime = 0

function start()
   terminal.newLine( 'Start state test' )

   focus = 0
   if not (world.terrainFocus() == focus) then
      if world.hasChunk( focus ) then
         world.setTerrainFocus( focus )
      end
   end

   if not engine.hasCamera() then
      camera = engine.newEntity( 'simple_cam' )
      engine.setCamera( camera )
   end

   if not world.hasEntity( 0, 1 ) then
      for i = 1,18 do
         tree = engine.newEntity( 'tree01' )
         world.addEntity( i, 1, tree )
         tree = engine.newEntity( 'tree01' )
         world.addEntity( i, 4, tree )
      end
      tree = engine.newEntity( 'tree01' )
      world.addEntity( 1, 3, tree )
      tree:printDebug()
   end

   if not world.hasEntity( 0, 0 ) then
      rock = engine.newEntity( 'rock01' )
      world.addEntity( 0, 0, rock )
   end

   game.setSunDir( 0, -1, -1 );
end

function update( dt )
   dtime = dtime + dt
   --print( 'Update state ' .. dt .. ' and ' .. dtime )
   --tree.transform:setPosition( 0, dtime / 4.0, 0 )

   angle1 = dtime*200
   rot1 = glm.rotate( angle1, 0.0, 1.0, 0.0 )
   axis2 = rot1:mul( glm.vec4( 0, -1, -1, 0.0 ) )

   game.setSunDir( axis2:get(0), axis2:get(1), axis2:get(2) )

   if dtime > 1 then
      engine.newState( 'test2' )
      dtime = 0
   end

end

function stop()
   terminal.newLine( 'Stop state test' )
end
