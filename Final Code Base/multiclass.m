% Neural Net for Connect 4
% Adapted from Löndahl, 2008

% Load data
load('allData.mat');
Attributes = X - 2;
Classifications = y;

% Constant
n = .01;
% Number of artificial nodes
nbrOfNodes = 8;
% Number of iterations forward and back
nbrOfEpochs = 0;
% Dimensions of the attributes matrix
e = size(Attributes);
% Number of training examples
nbrOfTrainExamples = e(1);
% Number of features
nbrOfFeatures = e(2);

% Sort into win vs not win
for i = 1:nbrOfTrainExamples
    if Classifications(i) == 3
        Classifications(i) = 1;
    else
        Classifications(i) = 0;
    end
end

% Initialize matrices with random weights 0-1
winWeights1 = rand(nbrOfNodes, nbrOfFeatures);
winWeights2 = rand(1, nbrOfNodes);

% For printing ERROR over time
figure;
hold on;

% Core loop
cnt = 0;
while cnt < nbrOfEpochs
    cnt = cnt + 1;
    fprintf('Iteration %d...\n', cnt);
    for i = 1:nbrOfTrainExamples
        % Attributes for this training example
        inputs = Attributes(i,:).';
        % The "correct" answer for this example
        targets = Classifications(i,:).';

        % Propagate the signals through network
        layer1 = activation(winWeights1*inputs);
        layer2 = activation(winWeights2*layer1);

        % Output layer error
        out_error = layer2.*(1-layer2).*(targets-layer2);

        % Calculate error for each node in hidden layer
        in_error = layer1.*(1-layer1).*(winWeights2.'*out_error);

        % Adjust the weights
        winWeights2 = winWeights2 + n.*out_error*(layer1.');
        winWeights1 = winWeights1 + n.*in_error*(inputs.');
    end

    RMS_Err = 0;
    for i=1:e(1)
        targets = Classifications(i,:).';
        inputs = Attributes(i,:).';
        RMS_Err = RMS_Err + norm(targets - activation(winWeights2*activation(winWeights1*inputs)),2);
    end
    z = RMS_Err/e(1);
    plot(cnt,log(z),'*');
end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Classifications = y;

% Sort into draw vs not draw
for i = 1:nbrOfTrainExamples
    if Classifications(i) == 2
        Classifications(i) = 1;
    else
        Classifications(i) = 0;
    end
end

% Initialize matrices with random weights 0-1
drawWeights1 = rand(nbrOfNodes, nbrOfFeatures);
drawWeights2 = rand(1, nbrOfNodes);

% For printing ERROR over time
figure;
hold on;

% Core loop
cnt = 0;
while cnt < nbrOfEpochs
    cnt = cnt + 1;
    fprintf('Iteration %d...\n', cnt);
    for i = 1:nbrOfTrainExamples
        % Attributes for this training example
        inputs = Attributes(i,:).';
        % The "correct" answer for this example
        targets = Classifications(i,:).';

        % Propagate the signals through network
        layer1 = activation(drawWeights1*inputs);
        layer2 = activation(drawWeights2*layer1);

        % Output layer error
        out_error = layer2.*(1-layer2).*(targets-layer2);

        % Calculate error for each node in hidden layer
        in_error = layer1.*(1-layer1).*(drawWeights2.'*out_error);

        % Adjust the weights
        drawWeights2 = drawWeights2 + n.*out_error*(layer1.');
        drawWeights1 = drawWeights1 + n.*in_error*(inputs.');
    end
    
    RMS_Err = 0;
    for i=1:e(1)
        targets = Classifications(i,:).';
        inputs = Attributes(i,:).';
        RMS_Err = RMS_Err + norm(targets - activation(drawWeights2*activation(drawWeights1*inputs)),2);
    end
    z = RMS_Err/e(1);
    plot(cnt,log(z),'*');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Classifications = y;

% Sort into loss vs not loss
for i = 1:nbrOfTrainExamples
    if Classifications(i) ~= 1
        Classifications(i) = 0;
    end
end

% Initialize matrices with random weights 0-1
lossWeights1 = rand(nbrOfNodes, nbrOfFeatures);
lossWeights2 = rand(1, nbrOfNodes);

% For printing ERROR over time
figure;
hold on;

% Core loop
cnt = 0;
while cnt < nbrOfEpochs
    cnt = cnt + 1;
    fprintf('Iteration %d...\n', cnt);
    for i = 1:nbrOfTrainExamples
        % Attributes for this training example
        inputs = Attributes(i,:).';
        % The "correct" answer for this example
        targets = Classifications(i,:).';

        % Propagate the signals through network
        layer1 = activation(lossWeights1*inputs);
        layer2 = activation(lossWeights2*layer1);

        % Output layer error
        out_error = layer2.*(1-layer2).*(targets-layer2);

        % Calculate error for each node in hidden layer
        in_error = layer1.*(1-layer1).*(lossWeights2.'*out_error);

        % Adjust the weights
        lossWeights2 = lossWeights2 + n.*out_error*(layer1.');
        lossWeights1 = lossWeights1 + n.*in_error*(inputs.');
    end
    
    RMS_Err = 0;
    for i=1:e(1)
        targets = Classifications(i,:).';
        inputs = Attributes(i,:).';
        RMS_Err = RMS_Err + norm(targets - activation(lossWeights2*activation(lossWeights1*inputs)),2);
    end
    z = RMS_Err/e(1);
    plot(cnt,log(z),'*');
    
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Test the accuracy
preds = zeros(1, nbrOfTrainExamples);
for i = 1:nbrOfTrainExamples
    w = predict(Attributes(i,:).', winWeights1, winWeights2);
    d = predict(Attributes(i,:).', drawWeights1, drawWeights2);
    l = predict(Attributes(i,:).', lossWeights1, lossWeights2);
    if ((w > d) && (w > l))
        preds(i) = 3;
    else
        if ((d > w) && (d > l))
            preds(i) = 2;
        else
            preds(i) = 1;
        end
    end  
end

fprintf('Training Set Accuracy: %d%%\n', ...
        round(mean(double(preds == y.')) * 100));
% h
function pred = predict(inputs, weights1, weights2)
    layer1 = activation(weights1*inputs);
    pred = activation(weights2*layer1);
end

% Sigmoid
function x = activation(x)
    x = 1./(1+exp(-x));
end