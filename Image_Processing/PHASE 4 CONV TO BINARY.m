%%Define Directory Arrays
DirectoryArray = {'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\00',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\01',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\02',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\03',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\04',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\05',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\06',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\07',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\08',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\09',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\10',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\11',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\12',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\13',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\15',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 3 - RENAMED AND MONOCHROME BITMAP\16',}

for i = 1:size(DirectoryArray,1)
  directory = dir(DirectoryArray{i});
  for j = 3:size(directory,1)
      startingfilePath = strcat(DirectoryArray{i}, '\', directory(j).name)
      
      A = imread(startingfilePath);
      endingFilePath = startingfilePath;
      endingFilePath(end) = 't';
      endingFilePath(end-1) = 'x';
      endingFilePath(end-2) = 't';
      file = fopen(endingFilePath, 'w');
      
      while (size(A,1)<520)
    
    A(end + 1, :) = 0;
end

B = A';
C = B(:);
C = C';
D = reshape(C,[8,size(C,2)/8]);
E = bitshift(uint8(D(1,:)),7) + bitshift(uint8(D(2,:)),6) + bitshift(uint8(D(3,:)),5) + bitshift(uint8(D(4,:)),4) + bitshift(uint8(D(5,:)),3) + bitshift(uint8(D(6,:)),2) + bitshift(uint8(D(7,:)),1) + bitshift(uint8(D(8,:)),0);
F = char(E);

fprintf(file,'%s',F);
fclose(file);

  end
end
    
%%Loop for the number of directorys.
    %%Loop for the files in the directorys
    %%Open Image
    %%Transpose Image
    %%Save Image.
%%A = imread('C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\0003.bmp');

%% LEFT OFF WITH A BINARY ARRAY... Matches image, if width is 360 and opened in notepad ++. Need to convert
%%B = reshape(AA,[size(A,1)/8],8)
%%C = bitshift(uint8(B(:,8)),7) + bitshift(uint8(B(:,7)),6) + bitshift(uint8(B(:,6)),5) + bitshift(uint8(B(:,5)),4) + bitshift(uint8(B(:,4)),3) + bitshift(uint8(B(:,3)),2) + bitshift(uint8(B(:,2)),1) + bitshift(uint8(B(:,1)),0)
%%dlmwrite('C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\test.bin',F,'')      

